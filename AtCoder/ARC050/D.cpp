#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> getSuffixArray(const auto& str, int alphabetSize){
	const int n = str.size();
	vector<pair<int, int>> vp(n);
	vector<int> rank(n), cnt(alphabetSize, 0);
	for(int i=0;i<n;i++) cnt[str[i]]++;
	for(int i=1;i<alphabetSize;i++) cnt[i] += cnt[i-1];
	for(int i=0;i<n;i++){
		rank[i] = vp[i].first = cnt[str[i]];
		vp[i].second = i;
	}
	sort(vp.begin(), vp.end());
	for(int h=1;h<n;h*=2){
		auto cur = vp.begin();
		while(cur != vp.end()){
			auto end = cur;
			int key = rank[cur->second];
			while(end != vp.end() && rank[end->second] == key){
				end->first = end->second + h < n ? rank[end->second + h] : -1;
				end++;
			}
			int s = distance(vp.begin(), cur), e = distance(vp.begin(), end);
			if(e - s > 1){
				sort(cur, end);
				rank[vp[e-1].second] = key;
				for(int i=e-2;i>=s;i--){
					rank[vp[i].second] = (vp[i].first == vp[i+1].first ? rank[vp[i+1].second] : key - (e-1-i));
				}
			}
			cur = end;
		}
	}
    vector<int> res(n);
	for(int i=0;i<n;i++) res[i] = vp[i].second;
    return res;
}

vector<int> getHeightArray(const vector<int> &SA, const auto &str){
	int n = SA.size();
	vector<int> rev(n);
	for(int i=0;i<n;i++) rev[SA[i]] = i;
    vector<int> res(n, 0);
	int prev = 0;
	for(int i=0;i<n;i++){
		int idx = rev[i];
		if(idx == n-1){ res[idx] = prev = 0; continue; }
		idx = SA[idx+1];
		int t = prev;
		while(max(i, idx)+t < n && str[i+t] == str[idx+t]) t++;
		res[rev[i]] = t;
		prev = max(0, t-1);
	}
    return res;
}

template<typename T>
class SegTree {
public:
    explicit SegTree(int n, T def) : N(calcN_(n)), def(def), mVal(2*calcN_(n)-1, def) {}
    void update(int idx, T value){
        int i = N + idx - 1;
        update_(mVal[i], value);
        while(i > 0){
            i = (i-1)/2;
            mVal[i] = operate(mVal[2*i+1], mVal[2*i+2]);
        }
    }
    T get(int l, int r){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        T res = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ res = operate(res, mVal[offset+l-1]); l++; }
            if(r&1){ res = operate(res, mVal[offset+r-2]); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N;
    while(cin >> N){
        string S; cin >> S;
        auto SA = getSuffixArray(S, 256);
        auto h = getHeightArray(SA, S);
        SegTree<int> seg(N, N+1);
        for(int i=0;i<N;i++) seg.update(i, h[i]);
        vector<int> rank(N, 0);
        for(int i=0;i<SA.size();i++) rank[SA[i]] = i;
        vector<int> res(N);
        for(int i=0;i<N;i++) res[i] = i;
        sort(res.begin(), res.end(), [&](int a, int b){
            int ra = rank[a];
            int rb = rank[b];
            int c = seg.get(min(ra, rb), max(ra, rb));
            if(c == N - max(a, b)){
                if(a < b){
                    int rc = rank[a+c];
                    int c2 = seg.get(min(ra, rc), max(ra, rc));
                    if(c2 < b-a) return rc < ra;
                } else {
                    int rc = rank[b+c];
                    int c2 = seg.get(min(rb, rc), max(rb, rc));
                    if(c2 < a-b) return rb < rc;
                }
            } else {
                return ra < rb;
            }
            return false;
        });
        for(auto& t : res) cout << t+1 << endl;
    }
}