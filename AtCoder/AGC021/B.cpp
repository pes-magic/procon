#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

template<typename T>
class P2 {
public:
	T x, y;
	P2(T x = 0, T y = 0) : x(x), y(y){}
	bool operator < (const P2<T>& p) const { return make_pair(x, y) < make_pair(p.x, p.y); }
	T length() const { return sqrt(x*x+y*y); }
	void sub(const P2<T>& p){ x -= p.x; y -= p.y; }
	void scale(T s){ x *= s; y *= s; }
};

template<typename T>
auto dot(const P2<T>& a, const P2<T>& b, const P2<T>& c){
	auto dx1 = b.x - a.x;
	auto dy1 = b.x - a.x;
	auto dx2 = c.x - b.x;
	auto dy2 = c.y - b.y;
	return dx1 * dx2 + dy1 * dy2;
}

template<typename T>
auto cross(const P2<T>& a, const P2<T>& b, const P2<T>& c){
	auto dx1 = b.x - a.x;
	auto dy1 = b.y - a.y;
	auto dx2 = c.x - b.x;
	auto dy2 = c.y - b.y;
	return dx1 * dy2 - dy1 * dx2;
}

template<typename T>
vector<P2<T>> convexHull(const vector<P2<T>>& ps){
	if(ps.size() <= 2) return ps;
	vector<P2<T>> pt = ps;
	sort(pt.begin(), pt.end());
	vector<P2<T>> res;
    auto addPoint = [&](auto& p, int lower){
		while(res.size() >= lower){
			int k = res.size();
			auto cr = cross(res[k-2], res[k-1], p);
			auto dt = dot(res[k-2], res[k-1], p);
			if(cr < 0 || (cr == 0 && dt >= 0)){
				res.pop_back();
			} else {
				break;
			}
		}
		res.push_back(p);
    };
	for(int i=0;i<pt.size();i++) addPoint(pt[i], 2);
	for(int i=pt.size()-2, t=res.size()+1;i>=0;i--) addPoint(pt[i], t);
	res.pop_back();
	return res;
}

int main(){
    int N; cin >> N;
    vector<P2<long long>> vp(N);
    for(auto& p : vp) cin >> p.x >> p.y;
    vector<double> res(N, 0.0);
    auto hull = convexHull(vp);
    for(int i=0;i<hull.size();i++){
        auto& prev = hull[(i+hull.size()-1)%hull.size()];
        auto& cur  = hull[i];
        auto& next = hull[(i+1)%hull.size()];
        auto x1 = cur.x - prev.x;
        auto y1 = cur.y - prev.y;
        auto x2 = next.x - cur.x;
        auto y2 = next.y - cur.y;
        auto rate = 0.5 * abs(atan2(x1*y2-x2*y1, x1*x2+y1*y2)) / acos(-1.0);
        for(int j=0;j<N;j++){
            if(cur.x == vp[j].x && cur.y == vp[j].y) res[j] = rate;
        }
    }
    for(auto& d : res) printf("%.8lf\n", d);
}