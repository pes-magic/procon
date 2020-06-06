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
    T operate(T a, T b) { return max(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<int> a(N);
    for(int i=0;i<N;i++) a[i] = i+1;
    SegTree<int> seg(N, 0);
    for(int i=0;i<Q;i++){
        int t, x, y; cin >> t >> x >> y;
        --x; --y;
        if(t == 1){
            swap(a[x], a[x+1]);
            seg.update(x, a[x] > a[x+1] ? 1 : 0);
            if(x-1 >= 0) seg.update(x-1, a[x-1] > a[x] ? 1 : 0);
            if(x+2 < N) seg.update(x+1, a[x+1] > a[x+2] ? 1 : 0);
        } else {
            if(seg.get(x, y) == 0) continue;
            while(seg.get(x, y) == 1){
                int L = x, R = y;
                while(R-L > 1){
                    int mid = (L+R)/2;
                    if(seg.get(x, mid) == 1) R = mid;
                    else L = mid;
                }
                while(L >= x && a[L] > a[L+1]){
                    swap(a[L], a[L+1]);
                    seg.update(L, 0);
                    if(L+2 < N) seg.update(L+1, a[L+1] > a[L+2] ? 1 : 0);
                    --L;
                }
                if(L >= 0) seg.update(L, a[L] > a[L+1] ? 1 : 0);
            }
        }
    }
    cout << a[0];
    for(int i=1;i<N;i++) cout << " " << a[i];
    cout << endl;
}