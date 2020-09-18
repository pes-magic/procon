#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class BIT {
public:
    explicit BIT(int n) : N(calcN_(n)), mVal(calcN_(n)+1, 0) {}
    void add(int idx, T val){
        for(int x=idx;x<=N;x+=x&-x) mVal[x] += val;
    }
    T sum(int idx){
        T res = 0;
        for(int x=idx;x>0;x-=x&-x) res += mVal[x];
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    const int N;
    vector<T> mVal;
};

int main(){
    int N, Q; cin >> N >> Q;
    BIT<long long> bit(N);
    for(int i=1;i<=N;i++){
        int a; cin >> a;
        bit.add(i, a);
    }
    for(int i=0;i<Q;i++){
        int t, l, r; cin >> t >> l >> r;
        if(t == 0){
            bit.add(l+1, r);
        } else {
            cout << bit.sum(r) - bit.sum(l) << endl;
        }
    }
}