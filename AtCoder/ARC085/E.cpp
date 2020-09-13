#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const long long INF = (1LL << 60);

template<typename T>
class MaxFlow {
public:
	explicit MaxFlow(int n) : g(n), level(n), iter(n) {}
    struct Edge {
        Edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
        int to, rev;
        T cap;
    };
	vector<vector<Edge>> g;
	vector<int> level;
	vector<int> iter;
	void addEdge(int src, int dst, T cap){
		g[src].emplace_back(dst, cap, g[dst].size());
		g[dst].emplace_back(src, 0, g[src].size()-1);
	}
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
};

int main(){
    int N; cin >> N;
    long long res = 0;
    MaxFlow<long long> mf(N+2);
    for(int i=1;i<=N;i++){
        int v; cin >> v;
        if(v < 0){
            mf.addEdge(0, i, -v);
        } else {
            mf.addEdge(i, N+1, v);
            res += v;
        }
        for(int j=2*i;j<=N;j+=i) mf.addEdge(i, j, INF);
    }
    cout << res - mf.maxFlow(0, N+1) << endl;
}