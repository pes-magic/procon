#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const double PI = acos(-1.0);

template<typename T>
int LIS(const vector<T>& v){
    if(v.empty()) return 0;
	vector<T> a(v.size(), v[0]);
    auto end = a.begin();
    ++end;
	for(int i=1;i<v.size();i++){
		auto l = lower_bound(a.begin(), end, v[i]);
        if(l == end) ++end;
        *l = v[i];
	}
	return distance(a.begin(), end);
}

int main(){
    int x1, y1, x2, y2;
    while(cin >> x1 >> y1 >> x2 >> y2){
        if(y1 > y2){
            swap(x1, x2);
            swap(y1, y2);
        }
        int sgn = (x1 <= x2 ? 1 : -1);
        x1 *= sgn;
        x2 *= sgn;
        int N; cin >> N;
        vector<pair<int, int>> vp;
        for(int i=0;i<N;i++){
            int x, y; cin >> x >> y;
            x *= sgn;
            if(x1 <= x && x <= x2 && y1 <= y && y <= y2){
                vp.emplace_back(x, y);
            }
        }
        int width = min(x2-x1, y2-y1) + 1;
        double res = 1e12;
        for(int _=0;_<2;_++){
            sort(vp.begin(), vp.end());
            vector<int> v(vp.size());
            for(int i=0;i<v.size();i++) v[i] = vp[i].second;
            int l = LIS(v);
            if(l == width){
                res = min(100.0*(x2-x1+y2-y1) + 5*PI + l * (5*PI - 20), res);
            } else {
                res = min(100.0*(x2-x1+y2-y1) + l * (5*PI - 20), res);
            }
            for(auto& p : vp) swap(p.first, p.second);
        }
        printf("%.12lf\n", res);
    }
}
