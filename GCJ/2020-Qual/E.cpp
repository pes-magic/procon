#include <iostream>
#include <vector>
#include <algorithm>

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

vector<vector<int>> solve(int N, int K){
    if(K == N+1 || K == N*N-1) return vector<vector<int>>();
    if(N <= 3 && K%N != 0) return vector<vector<int>>();
    vector<vector<int>> res(N, vector<int>(N, -1));
    vector<vector<int>> used(N, vector<int>(N, 0));
    for(int i=0;i<N;i++) res[i][i] = (K+i)/N;
    if(K%N == 1){ res[N-2][N-2]++; res[0][0]--; }
    if(K%N == N-1){
        res[1][1]--; res[N-1][N-1]++;
        for(int i=0;i<N-1-i;i++) swap(res[i][i], res[N-1-i][N-1-i]);
    }
    if(K%N == 1 || K%N == N-1){
        for(int i=1;i<N;i++){
            if(i+1 < N) res[i][i+1] = res[0][0];
            else res[i][1] = res[0][0];
        }
        res[0][N-1] = res[1][1];
        res[N-2][0] = res[1][1];
        res[N-1][N-2] = res[1][1];
        for(int i=0;i<N-2;i++){
            if(i-1 >= 0) res[i][i-1] = res[N-1][N-1];
            else res[i][N-3] = res[N-1][N-1];
        }
    } else if(K%N != 0){
        int idx = 0;
        for(int i=0;i<N;i++){
            if(res[i][i] != res[0][0]){ idx = i; break; }
        }
        for(int i=0;i<idx;i++){
            res[i][(i+1)%idx] = res[N-1][N-1];
        }
        for(int i=idx;i<N;i++){
            if(i+1 < N) res[i][i+1] = res[0][0];
            else res[N-1][idx] = res[0][0];
        }
    }
    vector<int> digit;
    for(int i=1;i<=N;i++){
        bool ok = true;
        for(auto& v : res){
            ok &= all_of(v.begin(), v.end(), [&](int t){ return t != i; });
        }
        if(ok) digit.push_back(i);
    }
    for(auto& d : digit){
        BipartiteMatch bm(N, N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) if(res[i][j] == -1) bm.addEdge(i, j);
        }
        bm.maximumMatch();
        for(int i=0;i<N;i++) res[i][bm.getMatch(i)] = d;
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int caseNum=1;caseNum<=T;caseNum++){
        int N, K; cin >> N >> K;
        auto res = solve(N, K);
        printf("Case #%d: %s\n", caseNum, res.empty() ? "IMPOSSIBLE" : "POSSIBLE");
        for(auto& v : res){
            cout << v[0];
            for(int i=1;i<N;i++) cout << " " << v[i];
            cout << endl;
        }
    }
}