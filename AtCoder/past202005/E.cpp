#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M, Q; cin >> N >> M >> Q;
    vector<vector<int>> g(N+1);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> c(N+1);
    for(int i=1;i<=N;i++) cin >> c[i];
    for(int i=0;i<Q;i++){
        int t, x; cin >> t >> x;
        cout << c[x] << endl;
        if(t == 1){
            for(auto& t : g[x]) c[t] = c[x];
        } else {
            int y; cin >> y;
            c[x] = y;
        }
    }
}