#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main(){
    double a, b, c, d, e, f;
    while(cin >> a >> b >> c >> d >> e >> f){
        e -= f;
        c /= a;
        d /= a;
        e /= a;
        printf("%.10lf\n", sqrt(0.25*(c*c+d*d)-e));
    }
}