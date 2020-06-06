#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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
    int N; cin >> N;
    vector<queue<int>> qu(N);
    SegTree<pair<int, int>> seg1(N, make_pair(0, 0));
    SegTree<pair<int, int>> seg2(N, make_pair(0, 0));
    for(int i=0;i<N;i++){
        int K; cin >> K;
        for(int j=0;j<K;j++){
            int T; cin >> T;
            qu[i].push(T);
        }
    }
    for(int i=0;i<N;i++){
        seg1.update(i, make_pair(qu[i].front(), i));
        qu[i].pop();
        if(!qu[i].empty()){
            seg2.update(i, make_pair(qu[i].front(), i));
            qu[i].pop();
        }
    }
    int M; cin >> M;
    for(int i=0;i<M;i++){
        int a; cin >> a;
        auto p1 = seg1.get(0, N);
        auto p2 = seg2.get(0, N);
        if(a == 1 || p1.first > p2.first){
            cout << p1.first << endl;;
            seg1.update(p1.second, seg2.get(p1.second, p1.second+1));
            if(qu[p1.second].empty()){
                seg2.update(p1.second, make_pair(0, 0));
            } else {
                seg2.update(p1.second, make_pair(qu[p1.second].front(), p1.second));
                qu[p1.second].pop();
            }
        } else {
            cout << p2.first << endl;
            if(qu[p2.second].empty()){
                seg2.update(p2.second, make_pair(0, 0));
            } else {
                seg2.update(p2.second, make_pair(qu[p2.second].front(), p2.second));
                qu[p2.second].pop();
            }
        }
    }
}