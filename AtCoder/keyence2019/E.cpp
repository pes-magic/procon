#include <iostream>
#include <vector>
#include <algorithm>

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
        return getImpl_(l, r, 0, 0, N);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return def;
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate(a, b);
    }
    T update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal; 
};

class UnionFind {
public:
    explicit UnionFind(int N) : root(N, -1), size(N, 1) {}
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    int getSize(int u){ return size[getRoot(u)]; }
    int same(int a, int b){
        return getRoot(a) == getRoot(b);
    }
    int merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u != v){
            root[u] = v;
            size[v] += size[u];
        }
    }
private:
    vector<int> root;
    vector<int> size;
};

int main(){
    int N; long long D;
    while(cin >> N >> D){
        vector<long long> A(N);
        for(auto& t : A) cin >> t;
        vector<pair<long long, int>> key;
        for(int i=0;i<N;i++) key.emplace_back(A[i], i);
        sort(key.begin(), key.end());
        SegTree<pair<long long, int>> left(N, make_pair(1LL << 60, -1));
        SegTree<pair<long long, int>> right(N, make_pair(1LL << 60, -1));
        vector<pair<long long, pair<int, int>>> edge;
        for(auto& p : key){
            int idx = p.second;
            int idxL = left.get(0, idx).second;
            int idxR = right.get(idx+1, N).second;
            if(idxL != -1){
                edge.emplace_back((idx-idxL)*D + p.first + A[idxL], make_pair(idxL, idx));
            }
            if(idxR != -1){
                edge.emplace_back((idxR-idx)*D + p.first + A[idxR], make_pair(idxR, idx));
            }
            left.update(idx, make_pair((N-idx)*D + A[idx], idx));
            right.update(idx, make_pair(idx*D + A[idx], idx));
        }
        long long res = 0;
        UnionFind uf(N);
        sort(edge.begin(), edge.end());
        for(auto & e : edge){
            int u = uf.getRoot(e.second.first);
            int v = uf.getRoot(e.second.second);
            if(u != v){
                uf.merge(u, v);
                res += e.first;
            }
        }
        cout << res << endl;
    }
}