#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    int a, b, c, d, e, f;
    while(cin >> a >> b >> c >> d >> e >> f){
        double div = a*e - d*b;
        printf("%.10lf %.10lf\n", (c*e - b*f)/div, (a*f - d*c)/div);
    }
}