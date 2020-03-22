#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    int L;
    while(cin >> L){
        double d = L/3.0;
        printf("%.12lf\n", d*d*d);
    }
}