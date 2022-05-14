#include <iostream>
#include <vector>
#include <string>

using namespace std;

int corner[10000];

int get(int x, int y, int N){
    int v = max(abs(x), abs(y));
    if(y == -v) return corner[v] + x + v;
    if(x == v) return corner[v] + 2*v + y + v;
    if(y == v) return corner[v] + 4*v + v - x;
    return corner[v] + 6*v + v - y;
}

vector<pair<int, int>> solve(int N, int K){
    {
        int cur = 1;
        for(int n=N-1;n>=0;n-=2){
            corner[n/2] = cur;
            cur += 4*n;
        }
    }
    vector<int> value;
    int cost = (N-1)/2*2;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    vector<pair<int,int>> res;
    if(K%2 == 1) return res;
    for(int n=N-1;n>0;n-=2){
        int x = -(n/2), y = -(n/2);
        for(int d=0;d<4;d++){
            if(cost <= K && K <= cost+n-2){
                x += dx[d] * (n/2 + (K-cost)/2);
                y += dy[d] * (n/2 + (K-cost)/2);
                while(x != 0 || y != 0){
                    pair<int,int> np = make_pair(x, y);
                    int cur = get(x, y, N);
                    int best = cur;
                    for(int i=0;i<4;i++){
                        int nx = x+dx[i], ny = y+dy[i];
                        if(max(abs(nx), abs(ny)) > (N-1)/2) continue;
                        int next = get(nx, ny, N);
                        if(next > best){
                            best = next;
                            np = make_pair(nx, ny);
                        }
                    }
                    if(best == cur) break;
                    if(best > cur+1){
                        res.emplace_back(cur, best);
                    }
                    x = np.first;
                    y = np.second;
                }
                return res;
            }
            x += dx[d] * n;
            y += dy[d] * n;
            cost += n/2 * 2;
            if(d==3) cost -= 2;
        }
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N, K; cin >> N >> K;
        auto res = solve(N, K);
        cout << "Case #" << t << ": ";
        if(res.empty()){
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << res.size() << endl;
            for(auto& p : res){
                cout << p.first << " " << p.second << endl;
            }
        }
    }
}