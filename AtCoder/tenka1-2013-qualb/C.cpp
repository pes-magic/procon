#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M, A, B;
    while(cin >> N >> M >> A >> B){
        vector<int> init(19*19*2*(1<<M), -1);
        auto dp = init;
        dp[0] = 0;
        for(int i=0;i<N;i++){
            const bool e1 = (i == 0 || i == N-1);
            for(int j=0;j<M;j++){
                const bool e2 = (j == 0 || j == M-1);
                auto next = init;
                for(int k=0;k<dp.size();k++){
                    if(dp[k] == -1) continue;
                    int t = k%(1<<M);
                    int up = 1 - t%2;
                    int left = 1 - (j == 0 ? 0 : k/(1<<M)%2);
                    int a = k/(2*(1<<M))%19;
                    int b = k/(19*2*(1<<M));
                    for(int r=0;r<=1;r++){
                        for(int d=0;d<=1;d++){
                            int nt = t/2 + (d<<(M-1));
                            int nl = r;
                            int na = a + (!e1 && !e2 && up + left + r + d == 4 ? 1 : 0);
                            int nb = b + (!e1 && !e2 && up + left + r + d == 0 ? 1 : 0);
                            int add = ((e1^e2) && up + left + r + d == 4 ? 1 : 0);
                            int idx = ((nb * 19 + na) * 2 + nl) * (1<<M) + nt;
                            next[idx] = max(next[idx], dp[k] + add);
                        }
                    }
                }
                dp = next;
            }
        }
        int res = 0;
        for(int k=0;k<dp.size();k++){
            int a = k/(2*(1<<M))%19;
            int b = k/(19*2*(1<<M));
            if(a >= A && b <= B) res = max(res, dp[k]);
        }
        cout << res << endl;
    }
}