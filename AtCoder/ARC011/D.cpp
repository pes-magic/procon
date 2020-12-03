#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

struct Line {
    explicit Line(double a, double b, double c) : a(a), b(b), c(c) {
        double d = max(abs(a), abs(b));
        a /= d;
        b /= d;
        c /= d;
    }
    double a, b, c;
};

struct Point {
    explicit Point(double x, double y) : x(x), y(y) {}
    double x, y;
};

double dist(const Line& l, const Point& p){
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a*l.a+l.b*l.b);
}

double sqDist(const Point& a, const Point& b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

void getDiv(vector<Line>& vl, int a1, int b1, int c1, int a2, int b2, int c2){
    double d1 = sqrt((double)a1*a1+b1*b1);
    double d2 = sqrt((double)a2*a2+b2*b2);
    if(a1*b2 != b1*a2){
        vl.emplace_back(a1/d1-a2/d2, b1/d1-b2/d2, c1/d1-c2/d2);
    }
    vl.emplace_back(a1/d1+a2/d2, b1/d1+b2/d2, c1/d1+c2/d2);
}

void getDiv(vector<Line>& vl, int x1, int y1, int x2, int y2){
    vl.emplace_back(2*(x2-x1), 2*(y2-y1), x1*x1+y1*y1-x2*x2-y2*y2);
}

int main(){
    int N, M, R; cin >> N >> M >> R;
    vector<int> a(N), b(N), c(N);
    vector<Line> road;
    for(int i=0;i<N;i++){
        cin >> a[i] >> b[i] >> c[i];
        if(a[i] < 0 || (a[i] == 0 && b[i] < 0)){
            a[i] = -a[i];
            b[i] = -b[i];
            c[i] = -c[i];
        }
        road.emplace_back(a[i], b[i], c[i]);
    }
    vector<int> p(M), q(M);
    vector<Point> house;
    for(int i=0;i<M;i++){
        cin >> p[i] >> q[i];
        house.emplace_back(p[i], q[i]);
    }
    vector<Line> all;
    all.emplace_back(1, 0, R);
    all.emplace_back(1, 0, -R);
    all.emplace_back(0, 1, R);
    all.emplace_back(0, 1, -R);
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++) getDiv(all, a[i], b[i], c[i], a[j], b[j], c[j]);
    }
    for(int i=0;i<M;i++){
        for(int j=i+1;j<M;j++) getDiv(all, p[i], q[i], p[j], q[j]);
    }
    double res = 0.0;
    for(int i=0;i<all.size();i++){
        for(int j=i+1;j<all.size();j++){
            double d = all[i].a*all[j].b-all[i].b*all[j].a;
            if(abs(d) < 1e-8) continue;
            double x = (all[i].b*all[j].c - all[i].c*all[j].b) / d;
            double y = -(all[i].a*all[j].c - all[i].c*all[j].a) / d;
            if(x < -(R+1e-8)|| R+1e-8 < x || y < -(R+1e-8)|| R+1e-8 < y) continue;
            Point cr(x, y);
            double p1 = 1e12, p2 = 1e12;
            for(auto& l : road) p1 = min(p1, dist(l, cr));
            for(auto& h : house) p2 = min(p2, sqDist(h, cr));
            res = max(res, p1+p2);
        }
    }
    printf("%.10lf\n", res);
}