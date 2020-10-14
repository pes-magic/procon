#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

int main(){
    int H, W; cin >> H >> W;
    vector<string> vs(H);
    for(auto& s : vs) cin >> s;
    int all = 0;
    for(auto& s : vs){
        for(auto& c : s) if(c == '.') all++;
    }
    vector<long long> pow2(all+1, 1);
    for(int i=0;i<all;i++) pow2[i+1] = pow2[i] * 2 % MOD;
    vector<vector<int>> cnt(H, vector<int>(W, 0));
    for(int i=0;i<H;i++){
        int idx = 0;
        while(idx < W){
            while(idx < W && vs[i][idx] == '#') ++idx;
            int end = idx;
            while(end < W && vs[i][end] == '.') ++end;
            for(int j=idx;j<end;j++) cnt[i][j] += end - idx;
            idx = end;
        }
    }
    for(int i=0;i<W;i++){
        int idx = 0;
        while(idx < H){
            while(idx < H && vs[idx][i] == '#') ++idx;
            int end = idx;
            while(end < H && vs[end][i] == '.') ++end;
            for(int j=idx;j<end;j++) cnt[j][i] += end - idx;
            idx = end;
        }
    }
    long long res = all * pow2[all] % MOD;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(vs[i][j] == '#') continue;
            res = (res + MOD - pow2[all-cnt[i][j]+1]) % MOD;
        }
    }
    cout << res << endl;
}