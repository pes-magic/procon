#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

int main(){
    int N, Q; cin >> N >> Q;
    vector<long long> h(N);
    for(auto& t : h) cin >> t;
    map<long long, int> mp;
    auto add = [&](int v){
        if(!mp.count(v)) mp[v] = 0;
        ++mp[v];
    };
    auto sub = [&](int v){
        if(!mp.count(v)){
            cout << v << endl;
            assert(false);
        }
        mp[v]--;
        if(mp[v] == 0) mp.erase(v);
    };
    for(int i=1;i<N;i+=2){
        add(h[i] - h[i-1]);
        if(i+1 < N) add(h[i] - h[i+1]);
    }
    long long ofs = 0;
    for(int i=0;i<Q;i++){
        long long q, t; cin >> q >> t;
        if(q == 1){
            ofs += t;
        } else if(q == 2){
            ofs -= t;
        } else {
            long long v; cin >> v;
            --t;
            if(t%2 == 0){
                if(t-1 >= 0){
                    sub(h[t-1] - h[t]);
                    add(h[t-1] - (h[t] + v));
                }
                if(t+1 < N){
                    sub(h[t+1] - h[t]);
                    add(h[t+1] - (h[t] + v));
                }
            } else {
                if(t-1 >= 0){
                    sub(h[t] - h[t-1]);
                    add(h[t] + v - h[t-1]);
                }
                if(t+1 < N){
                    sub(h[t] - h[t+1]);
                    add(h[t] + v - h[t+1]);
                }
            }
            h[t] += v;
        }
        if(mp.count(ofs)){
            cout << mp[ofs] << endl;
        } else {
            cout << 0 << endl;
        }
    }
}