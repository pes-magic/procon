#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Line {
    long long l, d, k, c;
    int A, B;
};

int main(){
    int N, M; cin >> N >> M;
    vector<Line> lines(M);
    vector<vector<int>> g(N);
    for(int i = 0; i < M; i++){
        cin >> lines[i].l >> lines[i].d >> lines[i].k >> lines[i].c >> lines[i].A >> lines[i].B;
        lines[i].A--;
        lines[i].B--;
        g[lines[i].B].push_back(i);
    }
    vector<long long> dist(N, 0);
    dist[N-1] = 1LL << 60;
    priority_queue<pair<long long, int>> qu;
    qu.push({1LL << 60, N-1});
    while(!qu.empty()){
        auto p = qu.top(); qu.pop();
        long long d = p.first;
        int v = p.second;
        if(dist[v] < d) continue;
        for(int i : g[v]){
            long long l = lines[i].l, d = lines[i].d, k = lines[i].k, c = lines[i].c, A = lines[i].A, B = lines[i].B;
            // l + n * d + c <= dist[v]
            // n * d <= dist[v] - l - c
            // n <= (dist[v] - l - c) / d
            long long t = (dist[v] - l - c) / d;
            if (t < 0) continue;
            t = min(t, k-1);
            t = l + t * d;
            if(dist[A] < t){
                dist[A] = t;
                qu.push({t, A});
            }
        }
    }
    dist.pop_back();
    for(auto t : dist){
        if(t == 0) cout << "Unreachable" << endl;
        else cout << t << endl;
    }


}