#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

double solve(const vector<int>& x, const vector<int>& c){
    auto func = [&](double p){
        double res = 0;
        for(int i=0;i<x.size();i++){
            res = max(res, abs(p - x[i]) * c[i]);
        }
        return res;
    };
    double L = -1e5, R = 1e5;
    for(int _=0;_<200;_++){
        double midA = (2*L+R)/3;
        double midB = (L+2*R)/3;
        if(func(midA) < func(midB)) R = midB;
        else L = midA;
    }
    return func((L+R)/2);
}

int main(){
    int N;
    while(cin >> N){
        vector<int> x(N), y(N), c(N);
        for(int i=0;i<N;i++) cin >> x[i] >> y[i] >> c[i];
        auto res = max(solve(x, c), solve(y, c));
        printf("%.10lf\n", res);
    }
}