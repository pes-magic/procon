#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m, k;
    while(cin >> n >> m >> k){
        vector<vector<vector<int>>> sum(k, vector<vector<int>>(n+1, vector<int>(m+1, 0)));
        vector<vector<int>> a(n+1, vector<int>(m+1));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin >> a[i][j];
                --a[i][j];
                ++sum[a[i][j]][i][j];
            }
        }
        for(auto& table : sum){
            for(int i=0;i<=n;i++){
                for(int j=0;j<m;j++) table[i][j+1] += table[i][j];
            }
            for(int j=0;j<=m;j++){
                for(int i=0;i<n;i++) table[i+1][j] += table[i][j];
            }
        }
        int q; cin >> q;
        for(int _=0;_<q;_++){
            int t, sx, sy, gx, gy;
            cin >> t >> sx >> sy >> gx >> gy;
            if(sx > gx) swap(sx, gx);
            if(sy > gy) swap(sy, gy);
            if(t == 1){
                if(sx == gx){
                    for(int i=sx;i<=n;i++){
                        --sum[a[sx][sy]][i][sy];
                        ++sum[a[gx][gy]][i][sy];
                    }
                } else {
                    for(int i=sy;i<=m;i++){
                        --sum[a[sx][sy]][sx][i];
                        ++sum[a[gx][gy]][sx][i];
                    }
                }
                swap(a[sx][sy], a[gx][gy]);
            } else {
                int best = 0, value = -1;
                for(int i=0;i<k;i++){
                    int cur = sum[i][gx][gy] - sum[i][sx-1][gy] - sum[i][gx][sy-1] + sum[i][sx-1][sy-1];
                    if(cur >= value){
                        best = i+1;
                        value = cur;
                    }
                }
                cout << best << " " << value << endl;
            }
        }
    }
}