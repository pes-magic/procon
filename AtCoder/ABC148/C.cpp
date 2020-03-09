#include <iostream>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }
long long lcm(long long a, long long b){ return a/gcd(a, b)*b; }

int main(){
    int a, b;
    while(cin >> a >> b){
        cout << lcm(a, b) << endl;
    }
}