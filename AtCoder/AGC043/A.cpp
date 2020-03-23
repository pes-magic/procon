#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main(){
    int H, W;
    while(cin >> H >> W){
        vector<string> vs(H);
        for(auto& s : vs) cin >> s;
        deque<pair<int,int>> qu;
        qu.emplace_front(0, 0);
        vector<vector<int>> dist(H, vector<int>(W, H*W+1));
        dist[0][0] = (vs[0][0] == '.' ? 0 : 1);
        while(!qu.empty()){
            auto pos = qu.front(); qu.pop_front();
            int dx[] = {0, 1};
            int dy[] = {1, 0};
            int x = pos.first;
            int y = pos.second;
            for(int i=0;i<2;i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx >= H || ny >= W) continue;
                int add = (vs[x][y] == '.' && vs[nx][ny] == '#' ? 1 : 0);
                int nc = dist[x][y] + add;
                if(nc < dist[nx][ny]){
                    dist[nx][ny] = nc;
                    if(add) qu.emplace_back(nx, ny);
                    else qu.emplace_front(nx, ny);
                }
            }
        }
        cout << dist[H-1][W-1] << endl;
    }
}