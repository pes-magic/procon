#include <iostream>
#include <vector>
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
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

class Node {
public:
    explicit Node(int src, int dst, pair<int,int> minA, pair<int,int> minB) : src(src), dst(dst), minA(minA), minB(minB) {}
    bool operator < (const Node& nd) const { return minA > nd.minA; }
    int src, dst;
    pair<int, int> minA, minB;
};

int main(){
    int N; cin >> N;
    vector<SegTree<pair<int, int>>> seg(2, SegTree<pair<int,int>>(N, make_pair(2*N, 2*N)));
    for(int i=0;i<N;i++){
        int a;
        cin >> a;
        seg[i%2].update(i, make_pair(a, i));
        seg[1-i%2].update(i, make_pair(2*N, i));
    }
    priority_queue<Node> qu;
    auto addNode = [&](int src, int dst){
        if(src >= dst) return;
        auto minA = seg[src%2].get(src, dst);
        auto minB = seg[1-src%2].get(minA.second+1, dst);
        qu.emplace(src, dst, minA, minB);
    };
    addNode(0, N);
    vector<int> res;
    while(!qu.empty()){
        auto nd = qu.top(); qu.pop();
        res.push_back(nd.minA.first);
        res.push_back(nd.minB.first);
        addNode(nd.src, nd.minA.second);
        addNode(nd.minA.second+1, nd.minB.second);
        addNode(nd.minB.second+1, nd.dst);
    }
    cout << res[0];
    for(int i=1;i<N;i++) cout << " " << res[i];
    cout << endl;
}