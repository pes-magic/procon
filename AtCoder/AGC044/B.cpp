#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(){
    int N; cin >> N;
    vector<vector<int>> dist(N, vector<int>(N));
    vector<vector<int>> c(N, vector<int>(N, 1));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            dist[i][j] = min(min(i, N-1-i), min(j, N-1-j));
        }
    }
    int res = 0;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    for(int p=0;p<N*N;p++){
        int P; cin >> P;
        int a = (P-1)%N;
        int b = (P-1)/N;
        c[a][b] = 0;
        res += dist[a][b];
        for(int i=0;i<4;i++){
            int na = a + dx[i];
            int nb = b + dy[i];
            if(na < 0 || N <= na || nb < 0 || N <= nb) continue;
            dist[a][b] = min(dist[a][b], dist[na][nb] + c[na][nb]);
        }
        deque<pair<int, int>> qu; qu.emplace_back(a, b);
        while(!qu.empty()){
            auto pr = qu.front(); qu.pop_front();
            int a = pr.first;
            int b = pr.second;
            for(int i=0;i<4;i++){
                int na = a + dx[i];
                int nb = b + dy[i];
                if(na < 0 || N <= na || nb < 0 || N <= nb) continue;
                if(dist[na][nb] <= dist[a][b] + c[a][b]) continue;
                dist[na][nb] = dist[a][b] + c[a][b];
                if(c[na][nb]) qu.emplace_back(na, nb);
                else qu.emplace_front(na, nb);
            }
        }
    }
    cout << res << endl;
}