#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    explicit Node(int dst, int cost) : dst(dst), cost(cost), edgeBest(0) {}
    int dst;
    int cost;
    long long edgeBest;
};

class Solver {
public:
    explicit Solver(int N) : g(N), parent(N), depth(N), rootDist(N), bestSum(N), rootBest(N), childBest(N), parentEdgeBest(N){
        read_();
        firstDFS_(0, -1, 0, 0);
        secondDFS_(0, -1, 0, 0);
    }
    long long query(int u, int v){
        int lca = getLCA_(u, v);
        long long res = rootDist[u] + rootDist[v] - 2 * rootDist[lca];
        res += rootBest[lca];
        res += childBest[lca];
        if(lca != u){
            res += childBest[u];
            int p = getParent_(u, depth[u] - depth[lca] - 1);
            res -= parentEdgeBest[p];
            res += bestSum[u] - bestSum[p];
        }
        if(lca != v){
            res += childBest[v];
            int p = getParent_(v, depth[v] - depth[lca] - 1);
            res -= parentEdgeBest[p];
            res += bestSum[v] - bestSum[p];
        }
        return res;
    }
private:
    void read_(){
        const int N = g.size();
        for(int i=0;i<N-1;i++){
            int A, B, C; cin >> A >> B >> C;
            --A; --B;
            g[A].emplace_back(B, C);
            g[B].emplace_back(A, C);
        }
    }
    void firstDFS_(int pos, int prev, int d, long long costSum){
        depth[pos] = d;
        rootDist[pos] = costSum;
        childBest[pos] = 0;
        parentEdgeBest[pos] = 0;
        if(prev >= 0){
            parent[pos].push_back(prev);
            int p = prev;
            while(parent[p].size() >= parent[pos].size()){
                parent[pos].push_back(parent[p][parent[pos].size()-1]);
                p = parent[pos].back();
            }
        }
        for(auto& pr : g[pos]){
            if(pr.dst == prev) continue;
            firstDFS_(pr.dst, pos, d+1, costSum + pr.cost);
            if(pr.cost >= 0){
                pr.edgeBest = pr.cost + max(0LL, childBest[pr.dst]);
            } else {
                pr.edgeBest = max(0LL, pr.cost + childBest[pr.dst]);
            }
            childBest[pos] += pr.edgeBest;
            parentEdgeBest[pr.dst] = pr.edgeBest;
        }
    }
    void secondDFS_(int pos, int prev, long long edgeCost, long long edgeBest){
        bestSum[pos] = 0;
        rootBest[pos] = 0;
        if(prev >= 0){
            bestSum[pos] = bestSum[prev] + childBest[prev] - edgeBest;
            rootBest[pos] = max(0LL, rootBest[prev] + childBest[prev] - edgeBest + edgeCost);
        }
        for(auto& pr : g[pos]){
            if(pr.dst == prev) continue;
            secondDFS_(pr.dst, pos, pr.cost, pr.edgeBest);
        }
    }
    int getLCA_(int u, int v){
        if(depth[u] > depth[v]) return getLCA_(v, u);
        v = getParent_(v, depth[v] - depth[u]);
        if(u == v) return u;
        for(int i=parent[u].size()-1;i>=0;i--){
            if(i < parent[u].size() && parent[u][i] != parent[v][i]){
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    }
    int getParent_(int pos, int d){
        for(int i=0;d;i++){
            if(d%2) pos = parent[pos][i];
            d /= 2;
        }
        return pos;
    }
private:
    vector<vector<Node>> g;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<long long> rootDist;
    vector<long long> bestSum;
    vector<long long> rootBest;
    vector<long long> childBest;
    vector<long long> parentEdgeBest;
};

int main(){
    int N;
    while(cin >> N){
        Solver solver(N);
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int U, V; cin >> U >> V;
            --U; --V;
            cout << solver.query(U, V) << endl;
        }
    }
}