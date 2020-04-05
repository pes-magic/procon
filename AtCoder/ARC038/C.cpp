#include <iostream>
#include <vector>

using namespace std;

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
        SegTree<int> seg(N, 2*N);
        vector<int> C(N), A(N), g(N);
        for(int i=1;i<N;i++) cin >> C[i] >> A[i];
        for(int i=0;i<N;i++) seg.update(i, i==0 ? 0 : -1);
        seg.update(0, 0);
        for(int i=1;i<N;i++){
            int L = 0, R = i+1;
            while(R-L > 1){
                int mid = (L+R)/2;
                if(seg.get(0, mid) >= i-C[i]) L = mid;
                else R = mid;
            }
            g[i] = L;
            seg.update(L, i);
        }
        int res = 0;
        for(int i=1;i<N;i++){
            if(A[i]%2 == 0) continue;
            res ^= g[i];
        }
        cout << (res ? "First" : "Second") << endl;
    }
}