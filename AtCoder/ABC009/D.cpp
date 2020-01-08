#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
public:
    explicit Matrix(int N) : m(N, vector<T>(N, 0)) {}
    static Matrix ident(int N) {
        Matrix res(N);
        for(int i=0;i<N;i++) res.m[i][i] = 1;
        return res;
    }
public:
    vector<vector<T>> m;
};

template<typename T>
Matrix<T> mul(const Matrix<T>& a, const Matrix<T>& b){
    const int N = a.m.size();
    Matrix<T> res(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res.m[i][j] = 0;
            for(int k=0;k<N;k++) res.m[i][j] += a.m[i][k] * b.m[k][j];
        }
    }
    return res;
}

template<typename T>
Matrix<T> pow(const Matrix<T>& a, int p){
    const int N = a.m.size();
    if(p == 0) return Matrix<T>::ident(N);
    auto res = pow(a, p/2);
    res = mul(res, res);
    if(p%2) res = mul(res, a);
    return res;
}

template<typename T>
vector<T> vecMul(const Matrix<T>& a, const vector<T>& v){
    const int N = a.m.size();
    vector<T> res(N, 0);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i] += a.m[i][j] * v[j];
        }
    }
    return res;
}

template<typename T>
Matrix<T> modMul(const Matrix<T>& a, const Matrix<T>& b, int mod){
    const int N = a.m.size();
    Matrix<T> res(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res.m[i][j] = 0;
            for(int k=0;k<N;k++){
                res.m[i][j] += a.m[i][k] * b.m[k][j];
            }
            res.m[i][j] %= mod;
        }
    }
    return res;
}

template<typename T>
Matrix<T> modPow(const Matrix<T>& a, int p, int mod){
    const int N = a.m.size();
    if(p == 0) return Matrix<T>::ident(N);
    auto res = modPow(a, p/2, mod);
    res = modMul(res, res, mod);
    if(p%2) res = modMul(res, a, mod);
    return res;
}

template<typename T>
vector<T> vecModMul(const Matrix<T>& a, const vector<T>& v, int mod){
    const int N = a.m.size();
    vector<T> res(N, 0);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i] += a.m[i][j] * v[j];
            res[i] %= mod;
        }
    }
    return res;
}

long long solve(const vector<long long>& A, const vector<long long>& C, int M){
    if(M <= A.size()) return A[M-1];
    long long res = 0;
    const int K = A.size();
    for(int i=0;i<32;i++){
        Matrix<int> a(K);
        for(int j=0;j<K-1;j++) a.m[j][j+1] = 1;
        for(int j=0;j<K;j++) a.m[K-1][j] = (C[K-j-1] >> i)%2;
        a = modPow(a, M-K, 2);
        vector<int> v(K);
        for(int j=0;j<K;j++) v[j] = (A[j] >> i)%2;
        if(vecModMul(a, v, 2).back()) res |= (1LL << i);
    }
    return res;
}

int main(){
    int K, M;
    while(cin >> K >> M){
        vector<long long> A(K), C(K);
        for(auto& t : A) cin >> t;
        for(auto& t : C) cin >> t;
        cout << solve(A, C, M) << endl;
    }
}