#include <iostream>
#include <vector>
#include <string>
#include <atcoder/maxflow>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<string> S(N);
    for(auto& s : S) cin >> s;
    atcoder::mf_graph<int> flow(N*M+2);
    int cnt = 0;
    for(int i=0;i<N;i++){
        for(int j=i%2;j<M;j+=2){
            if(S[i][j] == '#') continue;
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, -1, 0, 1};
            for(int d=0;d<4;d++){
                int nx = i+dx[d];
                int ny = j+dy[d];
                if(nx < 0 || N <= nx || ny < 0 || M <= ny || S[nx][ny] == '#') continue;
                flow.add_edge(i*M+j, nx*M+ny, 1);
                ++cnt;
            }
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(S[i][j] == '#') continue;
            if((i+j)%2 == 0) flow.add_edge(N*M, i*M+j, 1);
            else flow.add_edge(i*M+j, N*M+1, 1);
        }
    }
    cout << flow.flow(N*M, N*M+1) << endl;;
    for(int i=0;i<cnt;i++){
        auto e = flow.get_edge(i);
        if(!e.flow) continue;
        int src = e.from ,dst = e.to;
        if(src > dst) swap(src, dst);
        if(src+1 == dst && src%M != M-1){
            S[src/M][src%M] = '>';
            S[dst/M][dst%M] = '<';
        } else {
            S[src/M][src%M] = 'v';
            S[dst/M][dst%M] = '^';
        }
    }
    for(auto& s : S) cout << s << endl;
}
