#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int H, W, K;
    while(cin >> H >> W >> K){
        vector<string> vs(H, string(W, '#'));
        for(int i=0;i<K;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            vs[a][b] = '.';
        }
        vector<vector<int>> a(H, vector<int>(W, 0));
        vector<vector<int>> b(H, vector<int>(W, 0));
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                if(vs[i][j] == '#') a[i][j] = (i==0 ? 0 : a[i-1][j]) + 1;
            }
        }
        for(int i=H-1;i>=0;i--){
            for(int j=0;j<W;j++){
                if(vs[i][j] == '#') b[i][j] = (i==H-1 ? 0 : b[i+1][j]) + 1;
            }
        }
        int res = 0;
        for(int d=-H+1;d<=W-1;d++){
            int dh = max(0, -d);
            int dw = max(0, d);
            for(int j=0;j+dh<H && j+dw<W;j++){
                if(vs[j+dh][j+dw] == '.') continue;
                int k = j;
                while(k+dh < H && k+dw < W && vs[k+dh][k+dw] == '#') ++k;
                if(k - j <= res){
                    j = k;
                    continue;
                }
                for( ;j<k;++j){
                    if(b[j+dh][j+dw] <= res) continue;
                    for(int l=min(j + b[j+dh][j+dw], k)-1;l>=j;l--){
                        if(l-j+1 <= res) break;
                        if(a[l+dh][l+dw] >= l-j+1) res = max(res, l-j+1);
                    }
                }
            }
        }
        cout << res << endl;
    }
}