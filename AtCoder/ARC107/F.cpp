#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

const long long INF = 1LL << 50;

template<typename T>
class MaxFlow {
public:
	explicit MaxFlow(int n) : g(n), level(n), iter(n) {}
    struct Edge {
        Edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
        int to, rev;
        T cap;
    };
	void addEdge(int src, int dst, T cap){
		g[src].emplace_back(dst, cap, g[dst].size());
		g[dst].emplace_back(src, 0, g[src].size()-1);
	}
	T maxFlow(int s, int t){
		T res = 0;
		int n = g.size();
		while(true){
            fill(level.begin(), level.end(), -1);
			level[s] = 0;
			queue<int> qu; qu.push(s);
			while(!qu.empty()){
				int p = qu.front(); qu.pop();
				for(const Edge& e : g[p]){
					if(e.cap > 0 && level[e.to] == -1){
						level[e.to] = level[p]+1;
						qu.push(e.to);
					}
				}
			}
			if(level[t] == -1) break;
            fill(iter.begin(), iter.end(), 0);
			for(T f;(f=dfs(s, t, INF)) > 0;res+=f);
		}
		return res;
	}
    const vector<vector<Edge>>& getGraph() const { return g; }
private:
	T dfs(int pos, int dst, T f){
		if(pos == dst) return f;
		for(int& i=iter[pos];i<g[pos].size();++i){
			Edge& e = g[pos][i];
			if(e.cap == 0 || level[e.to] <= level[pos]) continue;
			int d = dfs(e.to, dst, min(f, e.cap));
			if(d > 0){
				e.cap -= d;
				g[e.to][e.rev].cap += d;
				return d;
			}
		}
		return 0;
	}
	vector<vector<Edge>> g;
	vector<int> level;
	vector<int> iter;
};

int main(){
    int N, M; cin >> N >> M;
    vector<long long> A(N), B(N);
    MaxFlow<long long> mf(2*N+2);
    for(auto& t : A) cin >> t;
    for(auto& t : B) cin >> t;
    long long res = 0;
    for(int i=0;i<N;i++){
        auto base = abs(B[i]);
        res += base;
        mf.addEdge(0, 2*i+1, base-B[i]);
        mf.addEdge(2*i+1, 2*i+2, base+A[i]);
        mf.addEdge(2*i+2, 2*i+1, INF);
        mf.addEdge(2*i+2, 2*N+1, base+B[i]);
    }
    for(int i=0;i<M;i++){
        int u, v; cin >> u >> v;
        --u; --v;
        mf.addEdge(2*u+2, 2*v+1, INF);
        mf.addEdge(2*v+2, 2*u+1, INF);
    }
    cout << res - mf.maxFlow(0, 2*N+1) << endl;
}
