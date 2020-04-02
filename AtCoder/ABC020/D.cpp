#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int countbit(int v){
    int res = 0;
    for(int i=v;i;i&=i-1) ++res;
    return res;
}

long long calc(int N, int K){
    vector<int> p;
    for(int i=2;i*i<=K;i++){
        if(K%i) continue;
        p.push_back(i);
        while(K%i == 0) K /= i;
    }
    if(K != 1) p.push_back(K);
    long long res = 0;
    for(int i=0;i<(1<<p.size());i++){
        int sgn = (countbit(i)%2 ? -1 : 1);
        long long m = 1;
        for(int j=0;j<p.size();j++){
            if(i&(1<<j)) m *= p[j];
        }
        long long add = (N/m)*(N/m+1)/2 % MOD * m % MOD;
        res = (res + MOD + sgn * add) % MOD;
    }
    return res;
}

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<int> divs;
        for(int i=1;i*i<=K;i++){
            if(K%i == 0){
                int d = K/i;
                divs.push_back(i);
                if(i != d) divs.push_back(d);
            }
        }
        long long res = 0;
        for(auto& d : divs) res += calc(N/d, K/d);
        cout << (res%MOD*K%MOD) << endl;
    }
}