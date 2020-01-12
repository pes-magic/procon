#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>

using namespace std;

const double EPS = 1e-10;
typedef complex<double> P;
typedef vector<P> G;

struct L { P p, q; L(P p, P q) : p(p), q(q) {} };

double dot(P a, P b) { return real(conj(a)*b); }
double cross(P a, P b) { return imag(conj(a)*b); }

P ssCrosspoint(L a, L b){
	double A = cross(a.q-a.p, b.q-b.p);
	double B = cross(a.q-a.p, a.q-b.p);
	return b.p + B/A * (b.q-b.p);
}

bool check(const vector<P>& vp, const P& c, double r){
    for(auto& p : vp){
        if(abs(p - c) > r + EPS) return false;
    }
    return true;
}

int main(){
    int N;
    while(cin >> N){
        vector<P> vp;
        for(int i=0;i<N;i++){
            int x, y; cin >> x >> y;
            vp.emplace_back(x, y);
        }
        double res = 1e10;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                P c1 = 0.5*(vp[i] + vp[j]);
                double r = abs(vp[i] - c1);
                if(check(vp, c1, r)){
                    res = min(res, r);
                }               
                for(int k=j+1;k<N;k++){
                    P c2 = 0.5*(vp[i]+vp[k]);
                    P q1 = c1 + (vp[j]-vp[i]) * P(0, 1);
                    P q2 = c2 + (vp[k]-vp[i]) * P(0, 1);
                    P d1 = (q1-c1)/abs(q1-c1);
                    P d2 = (q2-c2)/abs(q2-c2);
                    if(abs(cross(d1, d2)) < EPS) continue;
                    L l1 = L(c1, q1);
                    L l2 = L(c2, q2);
                    P test = ssCrosspoint(l1, l2);
                    r = abs(test - vp[i]);
                    if(check(vp, test, r)){
                        res = min(res, r);
                    }               
                }
            }
        }
        printf("%.8lf\n", res);
    }
}