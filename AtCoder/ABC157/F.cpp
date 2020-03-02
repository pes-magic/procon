#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>

using namespace std;

using P = complex<double>;
using Circle = pair<P,double>;

const double EPS = 1e-12;

bool overlap(const Circle& c1, const Circle& c2){
	auto d = abs(c1.first - c2.first);
	return c2.second - (d + c1.second) > -EPS;
}

bool inCircle(const Circle& c, const P& p){
	return c.second - abs(c.first-p) > -EPS;
}

bool crossCircle(const Circle& c1, const Circle& c2){
	auto r1 = c1.second;
	auto r2 = c2.second;
	auto d = abs(c1.first-c2.first);
	if(d < r1 || d < r2) return d - abs(r1 - r2) > EPS;
	return r1 + r2 - d > -EPS;
}

vector<P> crossPoint(const Circle& c1, const Circle& c2){
    if(!crossCircle(c1, c2)) return vector<P>();
	auto r1 = c1.second;
	auto r2 = c2.second;
	auto r3 = abs(c1.first - c2.first);
	auto rc = (r3*r3 + r1*r1 - r2*r2) / (2*r3);
	auto rs = sqrt(r1*r1 - rc*rc);
	P dif = (c2.first-c1.first)/r3;
    vector<P> res;
    res.emplace_back(c1.first + dif * P(rc,rs));
    res.emplace_back(c1.first + dif * P(rc,-rs));
	return res;
}

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<P> vp;
        vector<int> c(N);
        for(int i=0;i<N;i++){
            int x, y;
            cin >> x >> y >> c[i];
            vp.emplace_back(x, y);
        }
        double L = 0.0, R = 1000000.0;
        for(int _=0;_<200;_++){
            double mid = 0.5*(L+R);
            vector<Circle> vc;
            for(int i=0;i<N;i++) vc.emplace_back(vp[i], mid/c[i]);
            int mcnt = 0;
            for(int i=0;i<N;i++){
                vector<P> check;
                check.push_back(vp[i]);
                for(int j=i+1;j<N;j++){
                    auto cp = crossPoint(vc[i], vc[j]);
                    copy(cp.begin(), cp.end(), back_inserter(check));
                }
                for(auto& cr : check){
                    int cnt = 0;
                    for(int k=0;k<N;k++){
                        if(inCircle(vc[k], cr)) ++cnt;
                    }
                    mcnt = max(mcnt, cnt);
                }
            }
            if(mcnt >= K) R = mid;
            else L = mid;
        }
        printf("%.8lf\n", 0.5*(L+R));
    }
}