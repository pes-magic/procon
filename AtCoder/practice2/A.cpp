#include <iostream>
#include <atcoder/dsu>

using namespace std;

int main(){
    int N, Q; cin >> N >> Q;
    atcoder::dsu d(N);
    for(int _=0;_<Q;_++){
        int t, u, v; cin >> t >> u >> v;
        if(t == 0){
            d.merge(u, v);
        } else {
            cout << d.same(u, v) << endl;
        }
    }
}