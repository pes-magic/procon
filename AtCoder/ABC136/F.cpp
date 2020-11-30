#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MOD = 998244353;

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
        T resL = def;
        T resR = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ resL = operate(resL, mVal[offset+l-1]); l++; }
            if(r&1){ resR = operate(mVal[offset+r-2], resR); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return operate(resL, resR);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data += val; }
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N; cin >> N;
    vector<pair<int, int>> vp(N);
    vector<long long> p2(N+1);
    p2[0] = 1;
    for(int i=1;i<=N;i++) p2[i] = p2[i-1] * 2 % MOD;
    for(auto& p : vp) cin >> p.first >> p.second;
    long long res = N * (p2[N] + MOD - 1) % MOD;
    for(int i=0;i<4;i++){
        vector<int> crd;
        for(auto& p : vp){
            crd.push_back(p.first);
            crd.push_back(p.second);
        }
        sort(crd.begin(), crd.end());
        crd.erase(unique(crd.begin(), crd.end()), crd.end());
        map<int, int> idx;
        for(int i=0;i<crd.size();i++){
            idx[crd[i]] = i;
        }
        auto cur = vp;
        vector<vector<int>> x(crd.size());
        for(auto& c : cur){
            x[idx[c.second]].push_back(idx[c.first]);
        }
        SegTree<int> seg(crd.size(), 0);
        for(auto& v : x){
            for(auto& t : v){
                res += (p2[seg.get(0, t)] + MOD - 1);
                res += MOD - (p2[seg.get(0, crd.size())] + MOD - 1) % MOD;
            }
            for(auto& t : v){
                seg.update(t, 1);
            }
            res %= MOD;
        }
        for(auto& p : vp){
            int x = p.first, y = p.second;
            p.first = -y;
            p.second = x;
        }
    }
    cout << res << endl;
}