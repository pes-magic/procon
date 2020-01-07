#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    int K, N;
    while(cin >> K >> N){
        vector<vector<long long>> pair(K+1, vector<long long>(N+1, 0));
        vector<vector<long long>> solo(K+1, vector<long long>(N+1, 0));
        pair[0][0] = 1;
        solo[0][0] = 1;
        for(int i=1;i<=K;i++){
            long long sum = 0;
            for(int j=0;j<=N;j++){
                pair[i][j] += pair[i-1][j] + 2 * sum;
                pair[i][j] %= MOD;
                sum += pair[i-1][j];
                sum %= MOD;
            }
        }
        for(int i=1;i<=K;i++){
            long long sum = 0;
            for(int j=0;j<=N;j++){
                sum += solo[i-1][j];
                sum %= MOD;
                solo[i][j] = sum;
            }
        }
        vector<int> invalid(2*K+1, 0);
        for(int i=1;i<=K;i++){
            for(int j=i+1;j<=K;j++){
                ++invalid[i+j];
            }
        }
        for(int k=2;k<=2*K;k++){
            long long res = 0;
            int pr = invalid[k];
            if(k%2 == 0){
                for(int i=0;i<=N;i++){
                    res += pair[pr][i] * (solo[K-2*pr-1][N-i] + (i==N ? 0 : solo[K-2*pr-1][N-i-1]));
                    res %= MOD;
                }
            } else {
                for(int i=0;i<=N;i++){
                    res += pair[pr][i] * solo[K-2*pr][N-i];
                    res %= MOD;
                }
            }
            cout << res << endl;
        }
    }
}