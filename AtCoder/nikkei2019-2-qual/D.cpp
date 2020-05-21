#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1LL << 60;

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

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<pair<pair<int,int>, int>> vp(M);
        for(auto& p : vp){
            cin >> p.first.first >> p.first.second >> p.second;
            --p.first.first;
            --p.first.second;
        }
        sort(vp.begin(), vp.end());
        RangeUpdateQuery<long long> ruq(N, INF);
        ruq.update(0, 1, 0, 0);
        for(int i=0;i<M;i++){
            auto& p = vp[i];
            auto next = ruq.get(p.first.first) + p.second;
            if(ruq.get(p.first.second) <= next) continue;
            int L = p.first.first, R = p.first.second;
            while(R-L > 1){
                int mid = (L+R)/2;
                if(ruq.get(mid) > next) R = mid;
                else L = mid;
            }
            ruq.update(R, p.first.second+1, next, i+1);
        }
        auto res = ruq.get(N-1);
        cout << (res == INF ? -1 : res) << endl;
    }
}