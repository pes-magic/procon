#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, Q; cin >> N >> Q;
    vector<long long> r(N), c(N);
    for(int i=0;i<N;i++) r[i] = c[i] = i;
    bool swp = false;
    for(int i=0;i<Q;i++){
        int t; cin >> t;
        if(t == 1){
            int a, b; cin >> a >> b;
            if(!swp) swap(r[a-1], r[b-1]);
            else swap(c[a-1], c[b-1]);
        } else if(t == 2){
            int a, b; cin >> a >> b;
            if(!swp) swap(c[a-1], c[b-1]);
            else swap(r[a-1], r[b-1]);
        } else if(t == 3){
            // swap(r, c);
            swp = !swp;
        } else {
            int a, b; cin >> a >> b;
            --a; --b;
            if(swp) swap(a, b);
            cout << r[a]*N+c[b] << endl;
        }
    }
}