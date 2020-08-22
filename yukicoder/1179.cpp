#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main(){
    int a, b, c;
    while(cin >> a >> b >> c){
        if(a < 0){
            a = -a;
            b = -b;
            c = -c;
        }
        int D = b*b - 4*a*c;
        if(D > 0){
            printf("%.10lf %.10lf\n", 0.5*(-b-sqrt(D))/a, 0.5*(-b+sqrt(D))/a);
        } else if(D == 0){
            printf("%.10lf\n", 0.5*(-b)/a);
        } else {
            printf("imaginary\n");
        }
    }
}