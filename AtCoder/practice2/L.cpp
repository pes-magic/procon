#include <iostream>
#include <vector>
#include <atcoder/lazysegtree>

using namespace std;

struct Node {
    explicit Node(int z=0, int o=0, long long i=0) : zero(z), one(o), inv(i){}
    int zero, one;
    long long inv;
};

Node op(Node a, Node b){
    return Node(a.zero+b.zero, a.one+b.one, a.inv+b.inv+(long long)a.one * b.zero);
}

Node e() { return Node(0, 0, 0); }

Node mapping(bool f, Node s){
    if(!f) return s;
    const long long n = s.zero + s.one;
    return Node(s.one, s.zero, n*(n-1)/2-s.inv-s.zero*(s.zero-1)/2-s.one*(s.one-1)/2);
}

bool composition(bool a, bool b){ return a^b; }

bool id(){ return false; }

int main(){
    int N, Q; cin >> N >> Q;
    vector<Node> a(N);
    for(int i=0;i<N;i++){
        int t; cin >> t;
        if(t == 0) a[i].zero = 1;
        else a[i].one = 1;
    }
    atcoder::lazy_segtree<Node, op, e, bool, mapping, composition, id> seg(a);
    for(int i=0;i<Q;i++){
        int t, l, r; cin >> t >> l >> r;
        if(t == 1){
            seg.apply(l-1, r, true);
        } else {
            cout << seg.prod(l-1, r).inv << endl;
        }
    }
}
