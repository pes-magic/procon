#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> r(N), c(N);
    for(auto& t : r) cin >> t;
    c[0] = r[0];
    for(int i=1;i<N;i++) cin >> c[i];
    long long res[3] = {0, 0, 0};
    int met[3][3] = {
        {1, 2, 1},
        {2, 0, 0},
        {1, 0, 0}
    };
    for(int i=0;i<min(N-1, 3);i++){
        for(auto& t : r) res[t]++;
        for(auto& t : c) res[t]++;
        res[c[0]]--;
        int ns = r.size()-1;
        vector<int> nr(ns), nc(ns);
        nr[0] = nc[0] = met[r[1]][c[1]];
        for(int i=1;i<ns;i++) nr[i] = met[r[i+1]][nr[i-1]];
        for(int i=1;i<ns;i++) nc[i] = met[nc[i-1]][c[i+1]];
        r = nr;
        c = nc;
    }
    if(r.size() > 1){
        for(int i=0;i<r.size();i++) res[r[i]] += N-3-i;
        for(int i=1;i<c.size();i++) res[c[i]] += N-3-i;
    } else {
        res[r[0]]++;
    }
    cout << res[0] << " " << res[1] << " " << res[2] << endl;
}