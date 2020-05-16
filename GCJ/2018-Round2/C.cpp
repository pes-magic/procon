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

int solve(const vector<vector<int>>& A){
    int res = 0;
    const int N = A.size();
    for(int a=-N;a<=N;a++){
        BipartiteMatch bm(N, N);
        int cnt = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(A[i][j] != a) continue;
                ++cnt;
                bm.addEdge(i, j);
            }
        }
        res += cnt - bm.maximumMatch();
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        vector<vector<int>> A(N, vector<int>(N, 0));
        for(auto& v : A){
            for(auto& t : v) cin >> t;
        }
        printf("Case #%d: %d\n", t, solve(A));
    }
}