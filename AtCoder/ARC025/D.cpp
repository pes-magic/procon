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
Matrix<T> modPow(const Matrix<T>& a, long long p){
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
    long long H, W; cin >> H >> W;
    vector<Matrix<long long>> m(4, Matrix<long long>(4));
    m[0][0][0] = 1; m[0][0][1] = 1; m[0][0][2] = 1; m[0][0][3] = 1;
    m[0][1][0] = 1; m[0][1][1] = 0; m[0][1][2] = 1; m[0][1][3] = 0;
    m[0][2][0] = 1; m[0][2][1] = 1; m[0][2][2] = 0; m[0][2][3] = 0;
    m[0][3][0] = 2; m[0][3][1] = 1; m[0][3][2] = 1; m[0][3][3] = 1;

    m[1][1][0] = 1; m[1][1][1] = 1; m[1][1][2] = 1; m[1][1][3] = 1;
    m[1][3][0] = 1; m[1][3][1] = 1; m[1][3][2] = 0; m[1][3][3] = 0;

    m[2][2][0] = 1; m[2][2][1] = 1; m[2][2][2] = 1; m[2][2][3] = 1;
    m[2][3][0] = 1; m[2][3][1] = 0; m[2][3][2] = 1; m[2][3][3] = 0;

    m[3][3][0] = 1; m[3][3][1] = 1; m[3][3][2] = 1; m[3][3][3] = 1;


    int N; cin >> N;
    vector<pair<long long, long long>> query;
    vector<long long> pos;
    pos.push_back(0);
    pos.push_back(W);
    for(int i=0;i<N;i++){
        long long s, t; cin >> s >> t;
        query.emplace_back(s-1, t-1);
        pos.push_back(t-1);
        pos.push_back(t);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    map<int, int> idx;
    for(int i=0;i<pos.size();i++) idx[pos[i]] = i;
    vector<int> block(pos.size(), H==2 ? 0 : 2);
    SegTree<Matrix<long long>> seg(pos.size()-1, Matrix<long long>::ident(4));
    for(int i=0;i+1<pos.size();i++){
        seg.update(i, modPow(m[block[i]], pos[i+1]-pos[i]));
    }
    for(auto& q : query){
        int id = idx[q.second];
        block[id] ^= 1 << q.first;
        seg.update(id, m[block[id]]);
        auto all = seg.get(0, pos.size()-1);
        cout << (all[0][3] + all[1][3] + all[2][3] + all[3][3]) % MOD << endl;
    }
}