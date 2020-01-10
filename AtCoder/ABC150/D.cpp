#include <iostream>
#include <vector>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }
long long lcm(long long a, long long b){ return a/gcd(a,b)*b; }

int solve(vector<int> a, int M){
    int m = 1;
    while(true){
        int cnt = 0;
        for(auto& t : a) if(t%4 == 0) ++cnt;
        if(cnt == 0) break;
        if(cnt != a.size()) return 0;
        for(auto& t : a) t /= 2;
        m *= 2;
    }
    long long res = 1;
    for(auto& t : a){
        res = lcm(res, t);
        if(res / 2 * m > M) return 0;
    }
    res *= m;
    long long base = res/2;
    if(M < base) return 0;
    return 1 + (M-base)/res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<int> a(N);
        for(auto& t : a) cin >> t;
        cout << solve(a, M) << endl;
    }
}