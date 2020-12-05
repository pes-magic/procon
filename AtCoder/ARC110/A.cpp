#include <iostream>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }
long long lcm(long long a, long long b) { return a/gcd(a, b)*b; }

int main(){
    int N; cin >> N;
    long long res = 1;
    for(int i=1;i<=N;i++) res = lcm(res, i);
    cout <<res + 1 << endl;
}