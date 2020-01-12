#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const long long INF = 1LL << 60;

class Node {
public:
    explicit Node(int pos, int numB, long long cost) : numB(numB), pos(pos), cost(cost) {}
    bool operator < (const Node& nd) const { return cost > nd.cost; }
    int numB;
    int pos;
    long long cost;
};

vector<long long> solve(const vector<vector<int>>& ga, const vector<vector<int>>& gb){
    const int N = ga.size();
    vector<map<int, long long>> dist(N);
    vector<int> minB(N, N);
    minB[0] = 0;
    dist[0][0] = 0;
    priority_queue<Node> qu; qu.emplace(0, 0, 0);
    vector<long long> res(N, INF);
    while(!qu.empty()){
        auto p = qu.top(); qu.pop();
        if(minB[p.pos] == N) minB[p.pos] = p.numB;
        res[p.pos] = min(res[p.pos], p.cost);
        for(auto& next : ga[p.pos]){
            int nb = p.numB;
            if(nb > minB[next]) continue;
            long long nc = p.cost + 1;
            auto cur = dist[next].count(nb) ? dist[next][nb] : INF;
            if(cur > nc){
                dist[next][nb] = nc;
                qu.emplace(next, nb, nc);
            }
        }
        for(auto& next : gb[p.pos]){
            int nb = p.numB + 1;
            if(nb > minB[next]) continue;
            long long nc = p.cost + nb;
            auto cur = dist[next].count(nb) ? dist[next][nb] : INF;
            if(cur > nc){
                dist[next][nb] = nc;
                qu.emplace(next, nb, nc);
            }
        }
    }
    return res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<vector<int>>> g(2, vector<vector<int>>(N));
        for(int i=0;i<M;i++){
            int C, A, B; cin >> C >> A >> B;
            g[C][A].push_back(B);
            g[C][B].push_back(A);
        }
        auto res = solve(g[0], g[1]);
        for(auto& t : res) cout << t << endl;
    }
}