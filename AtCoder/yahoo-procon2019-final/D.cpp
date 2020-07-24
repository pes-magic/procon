#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MOD = 1000000007;

template<typename T>
class Matrix {
public:
    explicit Matrix(int N) : m(N, vector<T>(N, 0)) {}
    static Matrix ident(int N) {
        Matrix res(N);
        for(int i=0;i<N;i++) res.m[i][i] = 1;
        return res;
    }
    vector<T>& operator [](int n) { return m[n]; }
    const vector<T>& operator [](int n) const { return m[n]; }
    int size() const { return m.size(); }
public:
    vector<vector<T>> m;
};

template<typename T>
Matrix<T> modMul(const Matrix<T>& a, const Matrix<T>& b){
    const int N = a.size();
    Matrix<T> res(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i][j] = 0;
            for(int k=0;k<N;k++){
                res[i][j] += a[i][k] * b[k][j];
            }
            res[i][j] %= MOD;
        }
    }
    return res;
}

template<typename T>
Matrix<T> modPow(const Matrix<T>& a, int p){
    const int N = a.size();
    auto res = Matrix<T>::ident(N);
    auto m = a;
    while(true){
        if(p%2) res = modMul(res, m);
        p /= 2;
        if(!p) break;
        m = modMul(m, m);
    }
    return res;
}

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
        T resL = def;
        T resR = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ resL = operate(resL, mVal[offset+l-1]); l++; }
            if(r&1){ resR = operate(mVal[offset+r-2], resR); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return operate(resL, resR);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return modMul(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<pair<int, int>> query;
    vector<int> pos;
    for(int i=0;i<Q;i++){
        int t; cin >> t;
        if(t == 1){
            int p; cin >> p;
            query.emplace_back(p, -1);
            pos.push_back(p);
            pos.push_back(p+1);
        } else {
            int l, r; cin >> l >> r;
            query.emplace_back(l, r);
            pos.push_back(l);
            pos.push_back(r);
        }
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    map<int, int> idx;
    for(int i=0;i<pos.size();i++) idx[pos[i]] = i;
    Matrix<long long> empty(2);
    empty[0][0] = empty[0][1] = empty[1][0] = 1;
    Matrix<long long> stone(2);
    stone[1][0] = 1;
    SegTree<Matrix<long long>> seg(pos.size(), Matrix<long long>::ident(2));
    for(int i=0;i+1<pos.size();i++){
        seg.update(i, modPow(empty, pos[i+1]-pos[i]));
    }
    vector<int> block(pos.size(), 0);
    for(auto& q : query){
        if(q.second == -1){
            int i = idx[q.first];
            block[i] = 1 - block[i];
            seg.update(i, block[i] ? stone : empty);
        } else {
            int r = idx[q.second];
            if(block[r]){
                cout << 0 << endl;
            } else {
                cout << seg.get(idx[q.first], r)[0][0] << endl;
            }
        }
    }
}