#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
    vector<vector<int>> res(501, vector<int>(501, 0));
    for(int b=0;b<=500;b++){
        for(int i=500-b;i>=0;i--){
            for(int j=500;j>=0;j--){
                int s = 0;
                int t = 0;
                for(int w=(b==0?1:0);;w++){
                    s += w;
                    t += b;
                    if(i+t > 500) break;
                    if(j+s > 500) break;
                    res[i+t][j+s] = max(res[i+t][j+s], res[i][j]+(b>0?1:0)+w);
                }
            }
        }
    }
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int R, B; cin >> R >> B;
        printf("Case #%d: %d\n", t, res[R][B]);
    }
}