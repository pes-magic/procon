#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> x(N), y(N);
        for(int i=0;i<N;i++) cin >> x[i] >> y[i];
        double res = 0.0;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                res = max(res, hypot(x[i]-x[j], y[i]-y[j]));
            }
        }
        printf("%.10lf\n", res);
    }
}