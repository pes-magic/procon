#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    explicit Node(int pos, long long cost) : pos(pos), cost(cost) {}
    int pos;
    long long cost;
};

class Solver {
public:
    explicit Solver(int N) : N(N), g(N), upCost(N), upBest(N), pathSum(N), subBest(N), myBest(N), depth(N), parent(N) {
        read();
        preSearch(0, -1, 0, 0);
        postSearch(0, -1);
    }
    long long query(int u, int v){
        int lca = getLCA(u, v);
        if(u == lca) swap(u, v);
        long long res = upBest[lca];
        res += subBest[u] + pathSum[u] - pathSum[lca];
        if(v != lca) res += subBest[v] + pathSum[v] - pathSum[lca];
        if(v != lca) res -= subBest[lca];
        return res;
    }
private:
    void read(){
        for(int i=0;i<N-1;i++){
            int A, B, C; cin >> A >> B >> C;
            --A; --B;
            g[A].emplace_back(B, C);
            g[B].emplace_back(A, C);
        }
    }
    void preSearch(int pos, int prev, long long ecost, int d){
        // upCost, subBest, myBest, parent
        if(prev != -1){
            parent[pos].push_back(prev);
            while(parent[parent[pos].back()].size() >= parent[pos].size()){
                parent[pos].push_back(parent[parent[pos].back()][parent[pos].size()-1]);
            }
        }
        depth[pos] = d;
        for(auto& nd : g[pos]){
            if(nd.pos == prev) continue;
            preSearch(nd.pos, pos, nd.cost, d+1);
            subBest[pos] += myBest[nd.pos];
        }
        upCost[pos] = ecost;
        myBest[pos] = max(0LL, ecost + subBest[pos]);
    }
    void postSearch(int pos, int prev){
        if(prev != -1){
            long long add = subBest[prev] - myBest[pos] + upCost[pos];
            pathSum[pos] = pathSum[prev] + add;
            upBest[pos] = max(0LL, add + upBest[prev]);
        }
        for(auto& nd : g[pos]){
            if(nd.pos == prev) continue;
            postSearch(nd.pos, pos);
        }
    }
    int getParent(int pos, int d){
        int res = pos;
        for(int i=0;d;i++){
            if(d%2) res = parent[res][i];
            d /= 2;
        }
        return res;
    }
    int getLCA(int p, int q){
        if(depth[p] < depth[q]) swap(p, q);
        p = getParent(p, depth[p] - depth[q]);
        if(p == q) return p;
        for(int i=parent[p].size()-1;i>=0;i--){
            if(i >= parent[p].size()) continue;
            if(parent[p][i] != parent[q][i]){
                p = parent[p][i];
                q = parent[q][i];
            }
        }
        return parent[p][0];
    }
private:
    const int N;
    vector<vector<Node>> g;
    vector<long long> upCost;
    vector<long long> upBest;
    vector<long long> pathSum;
    vector<long long> subBest;
    vector<long long> myBest;
    vector<int> depth;
    vector<vector<int>> parent;
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