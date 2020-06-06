#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int N, X, Y; cin >> N >> X >> Y;
    X += 250;
    Y += 250;
    vector<vector<int>> w(500, vector<int>(500, 0));
    vector<vector<int>> s(500, vector<int>(500, -1));
    for(int i=0;i<N;i++){
        int x, y; cin >> x >> y;
        x += 250;
        y += 250;
        w[x][y] = 1;
    }
    int dx[] = {1, 0, -1, 1, -1, 0};
    int dy[] = {1, 1, 1, 0, 0, -1};
    s[250][250] = 0;
    queue<pair<int, int>> qu; qu.emplace(250, 250);
    while(!qu.empty()){
        auto p = qu.front(); qu.pop();
        int x = p.first;
        int y = p.second;
        for(int i=0;i<6;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || 500 <= nx || ny < 0 || 500 <= ny || w[nx][ny]) continue;
            if(s[nx][ny] != -1) continue;
            s[nx][ny] = s[x][y] + 1;
            qu.emplace(nx, ny);
        }
    }
    cout << s[X][Y] << endl;
}