#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int H, W, K;
    while(cin >> H >> W >> K){
        vector<string> vs(H);
        for(auto& s : vs) cin >> s;
        int ans = H+W;
        for(int div=0;div<(1<<(H-1));div++){
            int res = 0;
            for(int j=0;j<H-1;j++) res += (div>>j)%2;
            vector<int> cnt(H, 0);
            vector<int> add(H, 0);
            bool valid = true;
            for(int j=0;j<W;j++){
                fill(add.begin(), add.end(), 0);
                int idx = 0;
                add[idx] += vs[0][j] - '0';
                for(int k=0;k<H-1;k++){
                    if(div&(1<<k)) ++idx;
                    add[idx] += vs[k+1][j] - '0';
                }
                bool ok = true;
                for(int k=0;k<H;k++){
                    if(add[k] > K) valid = false;
                    if(cnt[k]+add[k] > K) ok = false;
                }
                if(ok){
                    for(int k=0;k<H;k++) cnt[k] += add[k];
                } else {
                    ++res;
                    cnt = add;
                }
            }
            if(valid) ans = min(res, ans);
        }
        cout << ans << endl;
    }
}
