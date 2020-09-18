#include <iostream>
#include <atcoder/scc>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    atcoder::scc_graph g(N);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        g.add_edge(a, b);
    }
    auto l = g.scc();
    cout << l.size() << endl;
    for(auto& v : l){
        cout << v.size();
        for(auto& t : v) cout << " " << t;
        cout << endl;
    }
}