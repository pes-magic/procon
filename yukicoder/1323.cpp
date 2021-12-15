#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

vector<vector<int>> calcStep(const vector<string>& vs, int rs, int cs){
    const int H = vs.size(), W = vs[0].size();
    vector step(H, vector(W, -1));
    queue<pair<int, int>> qu; qu.emplace(rs, cs);
    step[rs][cs] = 0;
    while(!qu.empty()){
        auto [r, c] = qu.front(); qu.pop();
        for(int d=0;d<4;d++){
            int nr = r+dx[d];
            int nc = c+dy[d];
            if(vs[nr][nc] == '#') continue;
            if(step[nr][nc] != -1) continue;
            step[nr][nc] = step[r][c] + 1;
            qu.emplace(nr, nc);
        }
    }
    return step;
}

int solve(const vector<string>& vs, int ra, int ca, int rb, int cb){
    const int H = vs.size(), W = vs[0].size();
    auto stepA = calcStep(vs, ra, ca);
    int dist = stepA[rb][cb];
    if(dist == -1) return -1;
    auto stepB = calcStep(vs, rb, cb);
    int cnt = 0;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(stepA[i][j] + stepB[i][j] == dist) ++cnt;
        }
    }
    if(cnt > dist+1) return 2*dist;
    int res = -1;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(vs[i][j] == '#') continue;
            if(stepA[i][j] == -1) continue;
            int deg = 0;
            for(int d=0;d<4;d++){
                if(vs[i+dx[d]][j+dy[d]] == '.') ++deg;
            }
            if(deg >= 3){
                if(stepA[i][j] != 0 && stepB[i][j] != 0 && stepA[i][j] + stepB[i][j] == dist) return 2*dist+2;
                else {
                    int d = min(stepA[i][j], stepB[i][j]);
                    if(res == -1 || 2*dist + 4*(d+1) < res) res = 2*dist + 4*(d+1);
                }
            }
        }
    }
    if(dist >= 1){
        auto vs2 = vs;
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                if(stepA[i][j] != 0 && stepB[i][j] != 0 && stepA[i][j] + stepB[i][j] == dist) vs2[i][j] = '#';
            }
        }
        vs2[rb][cb] = '#';
        auto stepC = calcStep(vs2, ra, ca);
        int d2 = -1;
        for(int d=0;d<4;d++){
            int nx = rb+dx[d], ny = cb+dy[d];
            if(stepC[nx][ny] > 0){
                if(d2 == -1 || stepC[nx][ny] < d2) d2 = stepC[nx][ny]+1;
            }
        }
        if(d2 != -1){
            if(res == -1 || dist+d2 < res) res = dist+d2;
        }
    }
    return res;
}

int main(){
    int H, W, ra, ca, rb, cb;
    while(cin >> H >> W >> ra >> ca >> rb >> cb){
        vector<string> vs(H);
        for(auto& s : vs) cin >> s;
        --ra; --ca; --rb; --cb;
        cout << solve(vs, ra, ca, rb, cb) << endl;
    }
}
