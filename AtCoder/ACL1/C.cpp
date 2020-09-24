#include <iostream>
#include <vector>
#include <string>
#include <atcoder/mincostflow>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<string> S(N);
    for(auto& s : S) cin >> s;
    atcoder::mcf_graph<int, int> mcf(2*N*M+2);
    const int THR = 100;
    int cap = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(S[i][j] == 'o') mcf.add_edge(2*N*M, i*M+j, 1, 0);
            if(S[i][j] != '#') mcf.add_edge(N*M+i*M+j, 2*N*M+1, 1, 0);
            if(S[i][j] != 'o') continue;
            ++cap;
            vector<vector<int>> dist(N, vector<int>(M, THR));
            dist[i][j] = 0;
            for(int k=i;k<N;k++){
                for(int l=j;l<M;l++){
                    if(S[k][l] == '#') continue;
                    if(dist[k][l] < THR){
                        mcf.add_edge(i*M+j, N*M+k*M+l, 1, THR-dist[k][l]);
                    }
                    if(k+1<N && S[k+1][l] != '#') dist[k+1][l] = min(dist[k+1][l], dist[k][l]+1);
                    if(l+1<M && S[k][l+1] != '#') dist[k][l+1] = min(dist[k][l+1], dist[k][l]+1);
                }
            }
        }
    }
    cout << cap*THR - mcf.flow(2*N*M, 2*N*M+1).second << endl;
}