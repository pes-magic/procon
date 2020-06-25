#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main(){
    int H, W, K; cin >> H >> W >> K;
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    --x1; --x2; --y1; --y2;
    vector<string> c(H);
    for(auto& s : c) cin >> s;
    vector dist = vector(H, vector(W, -1));
    queue<pair<int, int>> qu; qu.emplace(x1, y1);
    dist[x1][y1] = 0;
    while(!qu.empty()){
        auto p = qu.front(); qu.pop();
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, -1, 0, 1};
        for(int d=0;d<4;d++){
            for(int i=1;i<=K;i++){
                int nx = p.first + i * dx[d];
                int ny = p.second + i * dy[d];
                if(nx < 0 || H <= nx || ny < 0 || W <= ny || c[nx][ny] == '@') break;
                if(dist[nx][ny] != -1 && dist[nx][ny] < dist[p.first][p.second] + 1) break;
                if(dist[nx][ny] == -1){
                    dist[nx][ny] = dist[p.first][p.second] + 1;
                    qu.emplace(nx, ny);
                }
            }
        }
    }
    cout << dist[x2][y2] << endl;
}