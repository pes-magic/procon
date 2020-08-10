#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>

using namespace std;

const int MOD = 200003;

const double PI = acos(-1.0);
using P = complex<double>;

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

vector<long long> convolution(const vector<int>& a, const vector<int>& b){
    int _n = a.size() + b.size();
    int n = 1;
    while(n < _n) n *= 2;
    vector<P> na(n, P(0, 0)), nb(n, P(0, 0));
    for(int i=0;i<a.size();i++) na[i].real(a[i]);
    for(int i=0;i<b.size();i++) nb[i].real(b[i]);
    dft(na, 1);
    dft(nb, 1);
    vector<P> ab(n);
    for(int i=0;i<n;i++) ab[i] = na[i] * nb[i];
    dft(ab, -1);
    vector<long long> res(n);
    for(int i=0;i<n;i++) res[i] = (ab[i].real()/n + 0.5);
    return res;
}

int main(){
    int N; cin >> N;
    vector<int> p(MOD, 0);
    int m = 1;
    for(int i=0;i<MOD-1;i++){
        p[m] = i;
        m = 2*m%MOD;
    }
    vector<int> cnt(MOD-1, 0);
    long long res = 0;
    for(int i=0;i<N;i++){
        long long A; cin >> A;
        if(A == 0) continue;
        res -= A*A%MOD;
        cnt[p[A]]++;
    }
    auto cv = convolution(cnt, cnt);
    m = 1;
    for(int i=0;i<cv.size();i++){
        res += m * cv[i];
        m = 2*m%MOD;
    }
    cout << res/2 << endl;
}