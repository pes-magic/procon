// 行列累乗
// verified
// https://atcoder.jp/contests/abc009/tasks/abc009_4
// https://atcoder.jp/contests/ddcc2020-final/tasks/ddcc2020_final_b

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
    }
    return res;
}

template<typename T>
Matrix<T> modMul(const Matrix<T>& a, const Matrix<T>& b, int mod){
    const int N = a.size();
    Matrix<T> res(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i][j] = 0;
            for(int k=0;k<N;k++){
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= mod;
            }
            // res[i][j] %= mod; // 安全ならこっちでmodをとる
        }
    }
    return res;
}

template<typename T>
Matrix<T> modPow(const Matrix<T>& a, int p, int mod){
    const int N = a.size();
    auto res = Matrix<T>::ident(N);
    auto m = a;
    while(true){
        if(p%2) res = modMul(res, m, mod);
        p /= 2;
        if(!p) break;
        m = modMul(m, m, mod);
    }
    return res;
}

template<typename T>
vector<T> vecModMul(const Matrix<T>& a, const vector<T>& v, int mod){
    const int N = a.size();
    vector<T> res(N, 0);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            res[i] += a[i][j] * v[j];
            res[i] %= mod;
        }
    }
    return res;
}
