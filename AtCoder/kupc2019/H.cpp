#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000007;

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
    MaxFlow<int> mf(4*N+2);
    for(int i=0;i<N;i++){
        mf.addEdge(0, 4*i+1, INF);
        mf.addEdge(4*i+2, 4*i+1, INF);
        mf.addEdge(4*i+3, 4*i+2, INF);
        mf.addEdge(4*i+4, 4*i+3, INF);
        mf.addEdge(4*i+4, 4*N+1, INF);
    }
    for(int i=0;i<M;i++){
        int u, v, l; cin >> u >> v >> l;
        --u; --v;
        if(l == 0){
            mf.addEdge(4*u+1, 4*v+2, 1);
            mf.addEdge(4*u+2, 4*v+3, 1);
            mf.addEdge(4*u+3, 4*v+4, 1);
        } else {
            mf.addEdge(4*u+2, 4*v+2, 1);
            mf.addEdge(4*u+3, 4*v+3, 1);
        }
    }
    cout << mf.maxFlow(0, 4*N+1) << endl;
}