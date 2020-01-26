#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class RangeAddQuery {
public:
    explicit RangeAddQuery(int n) : N(calcN_(n)) {
        mVal.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        updateImpl_(l, r, value, 0, 0, N);
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            res += mVal[i];
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void updateImpl_(int l, int r, T value, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            mVal[idx] += value;
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
        }
    }
    const int N;
    vector<T> mVal; 
};

int main(){
    int N, D, A;
    while(cin >> N >> D >> A){     
        RangeAddQuery<long long> raq(N);
        vector<pair<long long, long long>> vp(N);
        for(auto& p : vp) cin >> p.first >> p.second;
        sort(vp.begin(), vp.end());
        for(int i=0;i<N;i++){
            raq.update(i, i+1, vp[i].second);
        }
        long long res = 0;
        int end = 0;
        for(int i=0;i<N;i++){
            while(end < N && vp[end].first <= vp[i].first + 2*D) ++end;
            int cur = raq.get(i);
            if(cur <= 0) continue;
            long long req = (cur + A - 1) / A;
            raq.update(i, end, -(req*A));
            res += req;
        }
        cout << res << endl;
    }
}
