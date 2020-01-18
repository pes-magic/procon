#include <iostream>
#include <vector>

using namespace std;

int main(){
    int p;
    while(cin >> p){
        vector<int> inv(p);
        vector<int> fact(p);
        vector<int> factInv(p);
        for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
        for(int i=2;i<=inv.size()-1;i++){
            inv[i] = inv[p % i] * (p - p / i) % p;
            fact[i] = fact[i-1] * i % p;
            factInv[i] = factInv[i-1] * inv[i] % p;
        }
        auto comb = [&](int n, int r){
            if(n < r) return 0;
            return fact[n] * factInv[n-r] % p * factInv[r] % p;
        };
        vector<int> b(p, 0);
        for(int i=0;i<p;i++){
            int a; cin >> a;
            if(!a) continue;
            b[0] = (b[0] + 1) % p;
            int m = 1;
            for(int j=p-1;j>=0;j--){
                int add = comb(p-1, j) * m % p;
                if((p-1-j)%2 == 0) add = (p - add) % p;
                b[j] = (b[j] + add) % p;
                m = (m * i) % p;
            }
        }
        cout << b[0];
        for(int i=1;i<p;i++) cout << " " << b[i];
        cout << endl;
    }
}