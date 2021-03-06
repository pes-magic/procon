#include <iostream>
#include <vector>
#include <complex>

using namespace std;

const double PI = acos(-1.0);
using P = complex<double>;

// void dft(vector<P>& v, int inv){
//     const int n = v.size();
//     if(n == 1) return;
//     vector<P> a(n/2), b(n/2);
//     for(int i=0;i<n/2;i++){
//         a[i] = v[2*i];
//         b[i] = v[2*i+1];
//     }
//     dft(a, inv);
//     dft(b, inv);
//     P cur = P(1, 0), rot = P(cos(2*PI/n), inv * sin(2*PI/n));
//     for(int i=0;i<n;i++){
//         v[i] = a[i%(n/2)] + b[i%(n/2)] * cur;
//         cur *= rot;
//     }
// }

void dft(vector<P>& v, int inv){
    const int n = v.size();
    int rev = 0;
    for(int i=1;i<n-1;i++){
        for(int j=n/2;j>(rev^=j);j/=2);
        if(i < rev) swap(v[i], v[rev]);
    }
    for(int m=1;m<n;m*=2){
        P cur = P(1, 0), rot = P(cos(PI/m), inv * sin(PI/m));
        for(int i=0;i<m;i++){
            for(int j=i;j<n;j+=2*m){
                P p = v[j];
                P q = v[j+m] * cur;
                v[j]   = p + q;
                v[j+m] = p - q;
            }
            cur *= rot;
        }
    }
}

vector<int> convolution(const vector<P>& a, const vector<P>& b){
    int _n = a.size() + b.size();
    int n = 1;
    while(n < _n) n *= 2;
    vector<P> na(n, P(0, 0)), nb(n, P(0, 0));
    for(int i=0;i<a.size();i++) na[i] = a[i];
    for(int i=0;i<b.size();i++) nb[i] = b[i];
    dft(na, 1);
    dft(nb, 1);
    vector<P> ab(n);
    for(int i=0;i<n;i++) ab[i] = na[i] * nb[i];
    dft(ab, -1);
    vector<int> res(n);
    for(int i=0;i<n;i++) res[i] = (ab[i].real()/n + 0.5);
    return res;
}

int main(){
    int N; cin >> N;
    vector<P> a, b;
    for(int i=0;i<N;i++){
        int x, y; cin >> x >> y;
        a.emplace_back(x, 0);
        b.emplace_back(y, 0);
    }
    auto res = convolution(a, b);
    cout << 0 << endl;
    for(int i=0;i<2*N-1;i++) cout << res[i] << endl;
}