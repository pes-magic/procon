#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<int> x, y;
    x.push_back(-1000000007);
    y.push_back(-1000000007);
    x.push_back(0);
    y.push_back(0);
    x.push_back(1000000007);
    y.push_back(1000000007);
    vector<int> A(N), B(N), C(N);
    vector<int> D(M), E(M), F(M);
    for(int i=0;i<N;i++){
        cin >> A[i] >> B[i] >> C[i];
        x.push_back(A[i]);
        x.push_back(B[i]);
        y.push_back(C[i]);
    }
    for(int i=0;i<M;i++){
        cin >> D[i] >> E[i] >> F[i];
        x.push_back(D[i]);
        y.push_back(E[i]);
        y.push_back(F[i]);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    map<int, int> xidx, yidx;
    for(int i=0;i<x.size();i++) xidx[x[i]] = i;
    for(int i=0;i<y.size();i++) yidx[y[i]] = i;
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, -1, 0, 1};
    vector canMove(x.size()-1, vector(y.size()-1, vector(4, 1)));
    vector visit(x.size()-1, vector(y.size()-1, 0));
    for(int i=0;i<N;i++){
        int a = xidx[A[i]];
        int b = xidx[B[i]];
        int c = yidx[C[i]];
        for(int j=a;j<b;j++){
            canMove[j][c-1][3] = canMove[j][c][1] = 0;
        }
    }
    for(int i=0;i<M;i++){
        int d = xidx[D[i]];
        int e = yidx[E[i]];
        int f = yidx[F[i]];
        for(int j=e;j<f;j++){
            canMove[d-1][j][2] = canMove[d][j][0] = 0;
        }
    }
    queue<pair<int, int>> qu; qu.emplace(xidx[0], yidx[0]);
    visit[xidx[0]][yidx[0]] = 1;
    bool ok = true;
    while(!qu.empty()){
        auto pr = qu.front(); qu.pop();
        auto cx = pr.first;
        auto cy = pr.second;
        if(cx == 0 || cx == x.size() - 2 || cy == 0 || cy == y.size() - 2){
            ok = false;
            break;
        }
        for(int i=0;i<4;i++){
            if(!canMove[cx][cy][i]) continue;
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(visit[nx][ny]) continue;
            visit[nx][ny] = 1;
            qu.emplace(nx, ny);
        }
    }
    if(ok){
        long long res = 0;
        for(int i=0;i<x.size()-1;i++){
            for(int j=0;j<y.size()-1;j++){
                if(!visit[i][j]) continue;
                long long dx = x[i+1] - x[i];
                long long dy = y[j+1] - y[j];
                res += dx * dy;
            }
        }
        cout << res << endl;
    } else {
        cout << "INF" << endl;
    }
}