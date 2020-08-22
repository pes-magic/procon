#include <iostream>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

int main(){
    int N; cin >> N;
    double a = PI*PI/6;
    double res = 1.0;
    for(int i=0;i<N;i++) res *= a;
    res /= N;
    cout << (int)res << endl;
}