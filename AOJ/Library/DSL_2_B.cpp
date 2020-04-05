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
    void update_(T& data, T val) { data += val; }
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal;
};


int main(){
    int n, q;
    while(cin >> n >> q){
        SegTree<int> seg(n, 0);
        for(int i=0;i<q;i++){
            int c, x, y; cin >> c >> x >> y;
            --x;
            if(c == 0){
                seg.update(x, y);
            } else {
                cout << seg.get(x, y) << endl;
            }
        }
    }
}
