#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

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
    int T, N;
    double P;
    while(cin >> T >> N >> P){
        RangeAddQuery<double> raq(T);
        vector<double> avgMul(T, 0.0);
        avgMul[0] = 1.0;
        for(int i=0;i<N;i++){
            double q; int x, t;
            cin >> q >> x >> t;
            if(T >= 2) avgMul[1] += P * q * (x - 1);
            if(t+1 < T) avgMul[t+1] -= P * q * (x - 1);
        }
        for(int i=1;i<T;i++) avgMul[i] += avgMul[i-1];
        for(auto& t : avgMul) t = log2(t);
        for(int i=0;i<T;i++) raq.update(i, T, avgMul[i]);
        double res = 0.0;
        for(int i=0;i<T;i++) res += pow(2.0, raq.get(i));
        printf("%.8lf\n", res);
    }
}