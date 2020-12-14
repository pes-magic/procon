#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1LL << 60;

int main(){
    int H, W; cin >> H >> W;
    vector B(H, vector(W, 0LL));
    for(auto& v : B){
        for(auto& t : v) cin >> t;
    }
    vector S(H+1, vector(W+1, 0LL));
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++) S[i+1][j+1] = S[i+1][j] + B[i][j];
    }
    for(int j=1;j<=W;j++){
        for(int i=1;i<=H;i++) S[i][j] += S[i-1][j];
    }
    auto getSum = [&](int sx, int sy, int ex, int ey){
        return S[ex][ey] - S[ex][sy] - S[sx][ey] + S[sx][sy];
    };
    vector bestH(H+1, vector(H+1, -INF));
    vector bestW(W+1, vector(W+1, -INF));
    for(int d=1;d<=H;d++){
        for(int i=0;i+d<=H;i++){
            bestH[i][i+d] = max(bestH[i][i+d-1], bestH[i+1][i+d]);
            long long lowest = 0;
            for(int j=1;j<=W;j++){
                auto cur = getSum(i, 0, i+d, j);
                bestH[i][i+d] = max(bestH[i][i+d], cur - lowest);
                lowest = min(lowest, cur);
            }
        }
    }
    for(int d=1;d<=W;d++){
        for(int j=0;j+d<=W;j++){
            bestW[j][j+d] = max(bestW[j][j+d-1], bestW[j+1][j+d]);
            long long lowest = 0;
            for(int i=1;i<=H;i++){
                auto cur = getSum(0, j, i, j+d);
                bestW[j][j+d] = max(bestW[j][j+d], cur - lowest);
                lowest = min(lowest, cur);
            }
        }
    }
    long long res = -INF;
    for(int i=1;i<H;i++) res = max(res, bestH[0][i]+bestH[i][H]);
    for(int i=1;i<W;i++) res = max(res, bestW[0][i]+bestW[i][W]);
    cout << res << endl;
}