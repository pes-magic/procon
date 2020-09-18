#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 1 << 30;

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
    vector<string> vs(N);
    for(auto& s : vs) cin >> s;
    MaxFlow<int> mf(N*M+2);
    for(int i=0;i<N;i++){
        for(int j=i%2;j<M;j+=2){
            if(vs[i][j] == '#') continue;
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, -1, 0, 1};
            for(int d=0;d<4;d++){
                int nx = i+dx[d];
                int ny = j+dy[d];
                if(nx < 0 || N <= nx || ny < 0 || M <= ny || vs[nx][ny] == '#') continue;
                mf.addEdge(i*M+j, nx*M+ny, 1);
            }
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if((i+j)%2) mf.addEdge(i*M+j, N*M+1, 1);
            else mf.addEdge(N*M, i*M+j, 1);
        }
    }
    cout << mf.maxFlow(N*M, N*M+1) << endl;
    auto& g = mf.getGraph();
    for(int i=0;i<N;i++){
        for(int j=i%2;j<M;j+=2){
            for(auto& e : g[i*M+j]){
                if(e.to < N*M && !e.cap){
                    int src = i*M+j;
                    int dst = e.to;
                    if(src > dst) swap(src, dst);
                    if(src+1 == dst && src%M != M-1){
                        vs[src/M][src%M] = '>';
                        vs[dst/M][dst%M] = '<';
                    } else {
                        vs[src/M][src%M] = 'v';
                        vs[dst/M][dst%M] = '^';
                    }
                }
            }
        }
    }
    for(auto& s : vs) cout << s << endl;
}