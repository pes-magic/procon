#include <iostream>
#include <vector>
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
        return getImpl_(l, r, 0, 0, N);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return def;
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate(a, b);
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
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        auto suf = getSuffixArray(A, 200001);
        vector<int> pos(N);
        SegTree<int> seg(N, N);
        for(int i=0;i<N;i++){
            seg.update(i, suf[i]);
            pos[suf[i]] = i;
        }
        vector<int> res(N);
        for(int i=0;i<N;i++){
            res[i] = seg.get(0, pos[i]);
            seg.update(pos[i], N);
        }
        for(auto& t : res) cout << t << endl;
    }
}