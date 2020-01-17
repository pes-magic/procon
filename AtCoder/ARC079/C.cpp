#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<int> a(N+1, 0), b(N+1, 0);
        for(int i=0;i<M;i++){
            int u, v; cin >> u >> v;
            if(u == 1) a[v] = 1;
            if(v == N) b[u] = 1;
        }
        bool ok = false;
        for(int i=2;i<N;i++) if(a[i] && b[i]) ok = true;
        cout << (ok ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }
}