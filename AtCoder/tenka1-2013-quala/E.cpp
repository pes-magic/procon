#include <iostream>
#include <vector>

using namespace std;

/*
.   #   .   #   .   #   .   #   .   #   .   #   .   #   .   #
..  ..  #.  #.  .#  .#  ##  ##  ..  ..  #.  #.  .#  .#  ##  ##
.   .   .   .   .   .   .   .   #   #   #   #   #   #   #   #
1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16

/*
A  DBA    D
BC  C    CB  C
D         A ABD
0  1    2   3
*/

bool finish = false;
int resX[36];
int resY[36];
int resD[36];

void solve(int t, vector<vector<int>>& v, const vector<string>& b, const vector<vector<int>> piece, vector<int>& use){
    const int H = v.size();
    const int W = v[0].size();
    if(finish) return;
    if(t == H*W){
        finish = true;
        for(int i=0;i<H*W/4;i++){
            cout << resY[i]+1 << " " << resX[i]+1 << " " << resD[i] << endl;
        }
        return;
    }
    const int x = t/W;
    const int y = t%W;
    if(v[x][y]){
        solve(t+1, v, b, piece, use);
        return;
    }
    const int d[4][4][2] = {
        {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
        {{0, 2}, {0, 1}, {1, 1}, {0, 0}},
        {{2, 0}, {1, 0}, {1, -1}, {0, 0}},
        {{1, -1}, {1, 0}, {0, 0}, {1, 1}}
    };
    for(int i=0;i<4;i++){
        bool ok = true;
        int id = 0;
        for(int j=0;j<4;j++){
            int nx = x + d[i][j][0];
            int ny = y + d[i][j][1];
            if(nx < 0 || H <= nx || ny < 0 || W <= ny || v[nx][ny]){
                ok = false;
                break;
            }
            id |= (b[nx][ny] == '#' ? 1 : 0) << j;
        }
        if(!ok) continue;
        if(use[id] == piece[id].size()) continue;
        resX[piece[id][use[id]]] = x + d[i][0][0];
        resY[piece[id][use[id]]] = y + d[i][0][1];
        resD[piece[id][use[id]]] = i;
        use[id]++;
        for(int j=0;j<4;j++){
            int nx = x + d[i][j][0];
            int ny = y + d[i][j][1];
            v[nx][ny] = 1;
        }
        solve(t+1, v, b, piece, use);
        for(int j=0;j<4;j++){
            int nx = x + d[i][j][0];
            int ny = y + d[i][j][1];
            v[nx][ny] = 0;
        }
        use[id]--;
    }
}

int main(){
    int H, W; cin >> H >> W;
    vector<vector<int>> v(H, vector<int>(W, 0));
    vector<string> b(H);
    for(auto& t : b) cin >> t;
    int N; cin >> N;
    vector<vector<int>> piece(16);
    vector<int> use(16, 0);
    for(int i=0;i<N;i++){
        int P; cin >> P;
        piece[P-1].push_back(i);
    }
    solve(0, v, b, piece, use);
    if(!finish) cout << -1 << endl;

}