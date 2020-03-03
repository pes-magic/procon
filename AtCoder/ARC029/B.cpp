#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

using P = complex<double>;

const double PI = acos(-1.0);

bool check(int A, int B, int C, int D){
    if(A <= C && B <= D) return true;
    if(C < B) return false;
    double L = 0.0, R = 0.5*PI;
    for(int _=0;_<100;_++){
        double mid = 0.5*(L+R);
        auto r = P(B, A);
        r *= P(cos(mid), sin(mid));
        if(r.imag() > C) L = mid;
        else R = mid;
    }
    auto p = P(B, -A);
    auto p2 = P(B, A);
    p *= P(cos(0.5*(L+R)), sin(0.5*(L+R)));
    p2 *= P(cos(0.5*(L+R)), sin(0.5*(L+R)));
    return p.real() <= D + 0.005;
}

int main(){
    int A, B;
    while(cin >> A >> B){
        if(B > A) swap(A, B);
        int N; cin >> N;
        for(int i=0;i<N;i++){
            int C, D;
            cin >> C >> D;
            cout << (check(A, B, C, D) || check(A, B, D, C) ? "YES" : "NO") << endl;
        }
    }
}