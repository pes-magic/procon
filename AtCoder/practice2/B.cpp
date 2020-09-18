#include <iostream>
#include <atcoder/fenwicktree>

using namespace std;

int main(){
    int N, Q; cin >> N >> Q;
    atcoder::fenwick_tree<long long> bit(N);
    for(int i=0;i<N;i++){
        int t; cin >> t;
        bit.add(i, t);
    }
    for(int i=0;i<Q;i++){
        int t, l, r; cin >> t >> l >> r;
        if(t == 0){
            bit.add(l, r);
        } else {
            cout << bit.sum(l, r) << endl;
        }
    }

}