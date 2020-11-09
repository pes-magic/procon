#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N, M, K; cin >> N >> M >> K;
    vector sum(N+1, vector(M+1, vector(10, 0)));
    for(int i=0;i<N;i++){
        string S; cin >> S;
        for(int j=0;j<M;j++){
            sum[i+1][j+1][S[j]-'0']++;
        }
    }
    for(int i=0;i<=N;i++){
        for(int j=0;j+1<=M;j++){
            for(int k=0;k<10;k++){
                sum[i][j+1][k] += sum[i][j][k];
            }
        }
    }
    for(int i=0;i+1<=N;i++){
        for(int j=0;j<=M;j++){
            for(int k=0;k<10;k++){
                sum[i+1][j][k] += sum[i][j][k];
            }
        }
    }
    int res = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            for(int k=1;i+k<=N&&j+k<=M;k++){
                int mx = 0;
                for(int l=0;l<10;l++){
                    mx = max(mx, sum[i+k][j+k][l]-sum[i][j+k][l]-sum[i+k][j][l]+sum[i][j][l]);
                }
                if(k*k - mx <= K) res = max(res, k);
            }
        }
    }
    cout << res << endl;
}