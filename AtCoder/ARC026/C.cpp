#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Edge {
public:
    explicit Edge(int pos, long long cost) : pos(pos), cost(cost) {}
    int pos;
    long long cost;
    bool operator < (const Edge& e) const { return cost > e.cost; }
};

int main(){
    int N, L;
    while(cin >> N >> L){
        vector<vector<Edge>> g(L+1);
        for(int i=0;i<L;i++) g[i+1].emplace_back(i, 0);
        for(int i=0;i<N;i++){
            int l, r, c; cin >> l >> r >> c;
            g[l].emplace_back(r, c);
        }
        vector<long long> dist(L+1, 1LL << 60);
        dist[0] = 0;
        priority_queue<Edge> qu; qu.emplace(0, 0);
        while(!qu.empty()){
            auto p = qu.top(); qu.pop();
            for(auto& e : g[p.pos]){
                auto next = dist[p.pos] + e.cost;
                if(dist[e.pos] > next){
                    dist[e.pos] = next;
                    qu.emplace(e.pos, next);
                }
            }
        }
        cout << dist.back() << endl;
    }
}