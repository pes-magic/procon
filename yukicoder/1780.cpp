#include <iostream>
#include <vector>
#include <string>

using namespace std;

const long long INF = (1LL << 50);

template<typename T>
class Matrix {
public:
    explicit Matrix(int N) : m(N, vector<T>(N, 0)) {}
    static Matrix ident(int N) {
        Matrix res(N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                res[i][j] = (i == j ? 0 : -INF);
            }
        }
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
            res[i][j] = -INF;
            for(int k=0;k<N;k++){
                if(a[i][k] == -INF || b[k][j] == -INF) continue;
                res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
            }
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

bool solve(){
    vector<int> C(26);
    for(auto& c : C){
        if(!(cin >> c)) return false;
        --c;
    }
    vector<int> K(26);
    for(auto& k : K) cin >> k;
    int N; cin >> N;
    vector<Matrix<long long>> v(26, Matrix<long long>::ident(16));
    for(int i=0;i<N;i++){
        string S; int A, B, E;
        cin >> S >> A >> B >> E;
        --A; --B;
        for(auto& s : S){
            if(v[s-'A'][A][B] < E){
                v[s-'A'][A][B] = v[s-'A'][B][A] = E;
            }
        }
    }
    vector<long long> res(16, 0);
    for(int i=0;i<26;i++){
        auto m = pow(v[i], K[i]);
        for(int j=0;j<16;j++){
            if(res[j] < -INF) continue;
            if(m[C[i]][j] == -INF){
                res[j] = -INF-1;
            } else {
                res[j] += m[C[i]][j];
            }
        }
    }
    long long best = -INF;
    for(auto& t : res) best = max(t, best);
    if(best == -INF){
        cout << "Impossible" << endl;
    } else {
        cout << best << endl;
    }
    return true;
}

int main(){
    while(solve());
}