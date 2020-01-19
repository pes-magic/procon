#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int bitCount(int t){
    int res = 0;
    for(int i=t;i;i&=i-1) res++;
    return res;
}

int main(){
    const int maxSize = 101;
	vector<long long> inv(maxSize);
	vector<long long> fact(maxSize);
	vector<long long> factInv(maxSize);
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
	auto comb = [&](int n, int r){
		if(n < r || r < 0) return 0LL;
		return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
	};
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    int H, W;
    vector<vector<vector<long long>>> stair(2, vector<vector<long long>>(11, vector<long long>(11, 0)));
    stair[0][0][0] = stair[1][0][0] = 1;
    for(int i=0;i<=10;i++){
        for(int j=0;j<=10;j++){
            for(int k=j+1;k<=10;k++){
                stair[1][i][k] += stair[0][i][j] * perm(k, k-j) % MOD * factInv[k-j];
                stair[1][i][k] %= MOD;
            }
            for(int k=i+1;k<=10;k++){
                stair[0][k][j] += stair[1][i][j] * perm(k, k-i) % MOD * factInv[k-i];
                stair[0][k][j] %= MOD;
            }
        }
    }
    vector<vector<long long>> stairSum(11, vector<long long>(11, 0));
    for(int i=0;i<=10;i++){
        for(int j=0;j<=10;j++){
            stairSum[i][j] = (stair[0][i][j] + stair[1][i][j]) % MOD;
        }
    }
    stairSum[0][0] = 1;
    vector<vector<long long>> val(11, vector<long long>(11, 0));
    for(int i=0;i<=10;i++){
        for(int j=0;j<=10;j++){
            for(int bi=0;bi<=i;bi++){
                for(int bj=0;bj<=j;bj++){
                    int wi = i - bi;
                    int wj = j - bj;
                    val[i][j] += stairSum[wi][bj] * stairSum[bi][wj] % MOD * comb(i, bi) % MOD * comb(j, bj) % MOD;
                    val[i][j] %= MOD;
                }
            }
        }
    }
    while(cin >> H >> W){
        vector<string> A(H);
        for(auto& s : A) cin >> s;
        long long res = stairSum[H][W];
        for(int mh=0;mh<(1<<H)-1;mh++){
            for(int mw=0;mw<(1<<W)-1;mw++){
                bool check = true;
                for(int i=0;i<H;i++){
                    if(mh&(1<<i)) continue;
                    bool ok = false;
                    char c = ' ';
                    for(int j=0;j<W;j++){
                        if(mw&(1<<j)) continue;
                        if(c == ' ') c = A[i][j];
                        else if(c != A[i][j]) ok = true;
                    }
                    if(!ok) check = false;
                }
                for(int j=0;j<W;j++){
                    if(mw&(1<<j)) continue;
                    bool ok = false;
                    char c = ' ';
                    for(int i=0;i<H;i++){
                        if(mh&(1<<i)) continue;
                        if(c == ' ') c = A[i][j];
                        else if(c != A[i][j]) ok = true;
                    }
                    if(!ok) check = false;
                }
                if(check){
                    res += val[bitCount(mh)][bitCount(mw)];
                    res %= MOD;
                }
            }
        }
        cout << res << endl;
    }
}