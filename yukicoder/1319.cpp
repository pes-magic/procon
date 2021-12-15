#include <iostream>
#include <cmath>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

int main(){
    double R, H, D; cin >> R >> H >> D;
    D *= 0.5;
    // auto area = [&](double d){
    //     return 0.5*H/R*(d*d*(log(d)-log(R+sqrt(R*R-d*d))) + R*sqrt(R*R-d*d));
    // };
    // double a = 0.0;
    // double pre = area(D);
    // double preD = D;
    // for(int i=1;i<=1000000;i++){
    //     double r = 0.000001 * i;
    //     double d = (1-r)*D + r * R;
    //     double a1 = area(0.5*(preD+d));
    //     double a2 = area(d);
    //     a += (d-preD)/6*(pre+4*a1+a2);
    //     preD = d;
    //     pre = a2;
    // }
    // printf("%.8lf\n", 4*a);
    double res = 1.0/6*H/R * R*R*R*0.5*PI - 1.0/6*H/R*(D*D*D*log(D) + 2*D*R*sqrt(R*R-D*D) + R*R*R*atan(D/sqrt(R*R-D*D)) - D*D*D*log(sqrt(R*R-D*D)+R));
    printf("%.8lf\n", 4*res);
}