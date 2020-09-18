#include <iostream>
#include <vector>
#include <atcoder/segtree>

using namespace std;

int op(int a, int b){ return max(a, b); }
int e(){ return -1; }

int main(){
    int N, Q; cin >> N >> Q;
    vector<int> A(N);
    for(auto& t : A) cin >> t;
    atcoder::segtree<int, op, e> seg(A);
    for(int i=0;i<Q;i++){
        int t, x, v; cin >> t >> x >> v;
        if(t == 1){
            seg.set(x-1, v);
        } else if(t == 2){
            cout << seg.prod(x-1, v) << endl;
        } else {
            cout << seg.max_right(x-1, [&](int t){ return t < v; }) + 1 << endl;
        }
    }
}