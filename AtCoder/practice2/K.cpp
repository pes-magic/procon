#include <iostream>
#include <vector>
#include <atcoder/lazysegtree>

using namespace std;

const int MOD = 998244353;

pair<long long, long long> op(pair<long long, long long> a, pair<long long, long long> b){
    return make_pair((a.first+b.first)%MOD, a.second+b.second);
}

pair<long long, long long> e() { return make_pair(0, 0); }

pair<long long, long long> mapping(pair<long long, long long> f, pair<long long, long long> s){
    return make_pair((s.first * f.first + s.second * f.second)%MOD, s.second);
}

pair<long long, long long> composition(pair<long long, long long> a, pair<long long, long long> b){
    return make_pair((a.first*b.first)%MOD, (b.second*a.first+a.second)%MOD);
}

pair<long long, long long> id(){ return make_pair(1, 0); }

int main(){
    int N, Q; cin >> N >> Q;
    vector<pair<long long, long long>> a(N, make_pair(1, 1));
    for(int i=0;i<N;i++) cin >> a[i].first;
    atcoder::lazy_segtree<pair<long long, long long>, op, e, pair<long long, long long>, mapping, composition, id> seg(a);
    for(int i=0;i<Q;i++){
        int t; cin >> t;
        if(t == 0){
            long long l, r, b, c; cin >> l >> r >> b >> c;
            seg.apply(l, r, make_pair(b, c));
        } else {
            int l, r; cin >> l >> r;
            cout << seg.prod(l, r).first << endl;
        }
    }
}
