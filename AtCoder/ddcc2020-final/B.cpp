#include <iostream>
#include <vector>

using namespace std;

class Func{
public:
	long long a, b;
	explicit Func(long long a = -1, long long b = -1) : a(a), b(b) {}
	Func operator += (const Func &p){
        if(b < 0) return *this = p;
        if(p.b < 0) return *this;
        a = max(a, p.a);
        b = max(b, p.b);
        return *this;
    }
    Func operator * (const Func &p) const {
        if(b < 0 || p.b < 0) return Func();
        return Func(a + p.a, max(b + p.a, p.b));
    }
};

template<typename T>
class Matrix {
public:
    explicit Matrix(int N) : m(N, vector<T>(N)) {}
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
            for(int k=0;k<N;k++) res[i][j] += a[i][k] * b[k][j];
        }
    }
    return res;
}

template<typename T>
Matrix<T> pow(const Matrix<T>& a, int p){
    const int N = a.size();
    if(p == 1) return a;
    auto res = pow(a, p/2);
    res = mul(res, res);
    if(p%2) res = mul(res, a);
    return res;
}

int main(){
    int N, M;
    long long W;
    int S, K;
    while(cin >> N >> M >> W >> S >> K){
        --S;
        Matrix<Func> m(N);
        for(int i=0;i<M;i++){
            int a, b, w; cin >> a >> b >> w;
            --a; --b;
            m[a][b] = Func(w, max(0, w));
        }
        m = pow(m, K);
        Func res;
        for(int i=0;i<N;i++) res += m[S][i];
        cout << (res.b < 0 ? -1 : max(W+res.a, res.b)) << endl;
    }
}