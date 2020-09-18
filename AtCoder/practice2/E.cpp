#include <iostream>
#include <vector>
#include <string>
#include <atcoder/mincostflow>

using namespace std;

const long long INF = 1LL << 30;

int main(){
    int N, K; cin >> N >> K;
    vector A(N, vector(N, 0));
    for(auto& v : A){
        for(auto& t : v) cin >> t;
    }
    atcoder::mcf_graph<int, long long> mcf(2*N+2);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            mcf.add_edge(i, N+j, 1, INF-A[i][j]);
        }
        mcf.add_edge(2*N, i, K, 0);
        mcf.add_edge(N+i, 2*N+1, K, 0);
    }
    mcf.add_edge(2*N, 2*N+1, N*K, INF);
    cout << N*K*INF - mcf.flow(2*N, 2*N+1, N*K).second << endl;
    vector<string> res(N, string(N, '.'));
    for(auto& e : mcf.edges()){
        if(e.from >= 2*N || e.to >= 2*N || !e.flow) continue;
        res[e.from][e.to-N] = 'X';
    }
    for(auto& s : res) cout << s << endl;
}