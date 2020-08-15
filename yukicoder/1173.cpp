#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<double> p(N), q(N);
        vector<int> A(N);
        for(auto& t : p) cin >> t;
        for(auto& t : q) cin >> t;
        for(auto& t : A) cin >> t;
        double L = 0.0, R = 1.0;
        for(int _=0;_<200;_++){
            double mid = 0.5*(L+R);
            double sum = 0.0;
            for(int i=0;i<N;i++) sum += p[i]*(1-q[i])/(1-q[i]*mid);
            if(sum > mid) L = mid;
            else R = mid;
        }
        double X = 0.5*(L+R);
        double res = 0.0;
        for(int i=0;i<N;i++){
            res += A[i] * (log(1-q[i]) - log(1-q[i]*X));
        }
        printf("%.10lf\n", res);
    }
}