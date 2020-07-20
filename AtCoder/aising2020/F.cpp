#include <iostream>
#include <vector>

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
Matrix<T> mul(const Matrix<T>& a, const Matrix<T>& b){
    const int N = a.size();
    Matrix<T> res(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i][j] = 0;
            for(int k=0;k<N;k++) res[i][j] += a[i][k] * b[k][j];
            res[i][j] %= MOD;
        }
    }
    return res;
}

template<typename T>
Matrix<T> pow(const Matrix<T>& a, int p){
    const int N = a.size();
    if(p == 0) return Matrix<T>::ident(N);
    auto res = pow(a, p/2);
    res = mul(res, res);
    if(p%2) res = mul(res, a);
    return res;
}

template<typename T>
vector<T> vecMul(const Matrix<T>& a, const vector<T>& v){
    const int N = a.size();
    vector<T> res(N, 0);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i] += a[i][j] * v[j];
        }
        res[i] %= MOD;
    }
    return res;
}

int solve(int N){
    Matrix<long long> m(21);
    for(int i=0;i<10;i+=2) m[i+1][i] = 1;
    for(int i=0;i<=10;i+=2){
        for(int j=1;j<=min(10, i+1);j+=2) m[i][j] = 1;
    }
    m[10][10] = 1;
    for(int i=11;i<=20;i++) m[i][i-1] = m[i][i] = 1;
    vector<long long> v(21, 0);
    for(int i=0;i<=10;i+=2) v[i] = 1;
    return vecMul(pow(m, N+5), v).back();
}

int main(){
    int T; cin >> T;
    for(int _=0;_<T;_++){
        int N; cin >> N;
        cout << solve(N) << endl;
    }
}