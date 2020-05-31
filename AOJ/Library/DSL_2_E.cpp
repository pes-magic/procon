#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class RangeAddQuery {
public:
    explicit RangeAddQuery(int n) : N(calcN_(n)) {
        mVal.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ update_(mVal[offset+l-1], value); l++; }
            if(r&1){ update_(mVal[offset+r-2], value); }
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
            update_(res, mVal[i]);
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    inline void update_(T& data, T val) { data += val; }
    const int N;
    vector<T> mVal;
};


int main(){
    int n, q;
    while(cin >> n >> q){
        RangeAddQuery<int> raq(n+1);
        for(int i=0;i<q;i++){
            int c; cin >> c;
            if(c == 0){
                int s, t, x; cin >> s >> t >> x;
                raq.update(s, t+1, x);
            } else {
                int p; cin >> p;
                cout << raq.get(p) << endl;
            }
        }
    }
}
