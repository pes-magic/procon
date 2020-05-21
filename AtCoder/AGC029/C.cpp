#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

template<typename T>
class RangeUpdateQuery {
public:
    explicit RangeUpdateQuery(int n, T def) : N(calcN_(n)) {
        mVal.assign(2*N+1, make_pair(-1, def));
    }
    void update(int l, int r, T value, int ts){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ mVal[offset+l-1].first = ts; mVal[offset+l-1].second = value; l++; }
            if(r&1){ mVal[offset+r-2].first = ts; mVal[offset+r-2].second = value; }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            res = max(mVal[i], res);
        }
        return res.second;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    const int N;
    vector<pair<int,T>> mVal;
};

bool valid(const vector<int>& a, const vector<int>& upper){
    const int N = a.size();
    RangeUpdateQuery<int> seg(N, 0);
    for(int i=1;i<a.size();i++){
        if(a[i] <= a[i-1]){
            int c = a[i];
            while(c >= 0){
                int v = seg.get(c);
                if(v == upper[c]-1){
                    seg.update(c, c+1, 0, i);
                    --c;
                } else {
                    seg.update(c, c+1, v+1, i);
                    break;
                }
            }
            if(c < 0) return false;
        } else {
            seg.update(a[i-1]+1, a[i]+1, 0, i);
        }
    }
    return true;
}

long long pow(long long a, long long p){
    if(a == 1) return 1;
    if(p == 0) return 1;
    auto res = pow(a, p/2);
    res *= res;
    if(p%2 == 1) res *= a;
    return min(res, 200000LL);
}

int main(){
    int N; cin >> N;
    vector<int> a(N);
    vector<int> v;
    for(auto& t : a){
        cin >> t;
        v.push_back(t);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    map<int, int> idx;
    for(int i=0;i<v.size();i++) idx[v[i]] = i;
    for(auto& t : a) t = idx[t];
    int L = 0, R = N;
    vector<int> upper(N);
    while(R-L > 1){
        int mid = (L+R)/2;
        upper[0] = pow(mid, v[0]);
        for(int i=1;i<N;i++) upper[i] = pow(mid, v[i]-v[i-1]);
        if(valid(a, upper)) R = mid;
        else L = mid;
    }
    cout << R << endl;
}