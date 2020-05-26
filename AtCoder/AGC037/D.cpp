#include <iostream>
#include <vector>

using namespace std;

class BipartiteMatch {
public:
    explicit BipartiteMatch(int N, int M) :
        N(N), M(M), g(N+M), match(N+M, -1), visit(N+M, 0)
    {}
public:
    void addEdge(int a, int b){
        g[a].push_back(b+N);
        g[b+N].push_back(a);
    }
    int maximumMatch(){
        int res = 0;
        fill(match.begin(), match.end(), -1);
        for(int i=0;i<N;i++){
            fill(visit.begin(), visit.end(), 0);
            if(search_(i)) ++res;
        }
        return res;
    }
    int getMatch(int t) const { return t < N ? match[t] - N : match[t]; }
private:
    bool search_(int u){
        if(u < 0) return true;
        for(auto next : g[u]){
            if(visit[next]) continue;
            visit[next] = 1;
            if(search_(match[next])){
                match[u] = next, match[next] = u;
                return true;
            }
        }
        return false;
    }
private:
    const int N, M;
    vector<vector<int>> g;
    vector<int> match;
    vector<int> visit;
};

int main(){
    int N, M; cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M));
    vector<vector<vector<int>>> val(N, vector<vector<int>>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int a; cin >> a;
            val[i][(a-1)/M].push_back(a);
        }
    }
    vector<vector<int>> B(N);
    vector<vector<int>> C(N);
    for(int i=0;i<M;i++){
        BipartiteMatch bm(N, N);
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                if(!val[j][k].empty()) bm.addEdge(j, k);
            }
        }
        bm.maximumMatch();
        for(int j=0;j<N;j++){
            int m = bm.getMatch(j);
            int b = val[j][m].back();
            val[j][m].pop_back();
            B[j].push_back(b);
            C[(b-1)/M].push_back(b);
        }
    }
    for(auto& v : B){
        cout << v[0];
        for(int i=1;i<v.size();i++) cout << " " << v[i];
        cout << endl;
    }
    for(auto& v : C){
        cout << v[0];
        for(int i=1;i<v.size();i++) cout << " " << v[i];
        cout << endl;
    }
}