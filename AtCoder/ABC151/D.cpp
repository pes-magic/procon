#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int solve(const vector<string>& vs, int sx, int sy){
    int W = vs[0].size();
    int H = vs.size();
    vector<vector<int>> step(H, vector<int>(W, 1000000));
    step[sx][sy] = 0;
    queue<pair<int,int>> qu; qu.emplace(sx, sy);
    int res = 0;
    while(!qu.empty()){
        auto p = qu.front(); qu.pop();
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};
        for(int i=0;i<4;i++){
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
            if(nx < 0 || H <= nx || ny < 0 || W <= ny || vs[nx][ny] == '#') continue;
            int ns = step[p.first][p.second] + 1;
            if(ns < step[nx][ny]){
                step[nx][ny] = ns;
                qu.emplace(nx, ny);
                res = max(res, ns);
            }
        }
    }
    return res;
}

int main(){
    int H, W;
    while(cin >> H >> W){
        vector<string> vs(H);
        for(auto& s : vs) cin >> s;
        int res = 0;
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                if(vs[i][j] == '#') continue;
                res = max(res, solve(vs, i, j));
            }
        }
        cout << res << endl;
    }
}