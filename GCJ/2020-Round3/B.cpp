#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int solveSmall(int K, const vector<int>& X, const vector<int> T){
    int res = 2*K;
    vector<int> seg(2*K, 0), id(2*K, 0);
    for(auto& t : X) seg[2*t] = 1;
    for(int i=0;i<X.size();i++){
        for(int j=2*X[i];j<(i+1==X.size()?2*K:2*X[i+1]);j++) id[j] = i;
    }
    for(int i=0;i<1<<(2*K);i++){
        bool ok = true;
        for(int j=0;j<2*K;j++) if((i&(1<<j)) && seg[j]) ok = false;
        if(!ok) continue;
        for(int j=0;j<X.size();j++){
            int v = (1 << ((j+1==X.size()?2*K:2*X[j+1]) - 2*X[j])) - 1;
            v <<= 2*X[j];
            if(!(v&i)) ok = false;
        }
        if(!ok) continue;
        vector<int> pos;
        for(int j=0;j<2*K;j++) if(i&(1<<j)) pos.push_back(j);
        for(int j=0;j<pos.size() && ok;j++){
            int cur = pos[j];
            int next = pos[(j+1)%pos.size()];
            if(id[cur] == id[next]) continue;
            if(cur%2 != next%2){ ok = false; continue; }
            int dst = (cur < next ? next : next + 2*K);
            for(int k=cur+1;k<dst;k++){
                int c = k-cur < dst-k ? id[cur] : id[next];
                if(c != id[k%(2*K)]) ok = false;
            }
        }
        if(ok) res = min<int>(res, pos.size());
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int tc=1;tc<=T;tc++){
        int K, N; cin >> K >> N;
        vector<int> X(N), T(N);
        for(auto& t : X) cin >> t;
        for(auto& t : T) cin >> t;
        int ofs = X[0];
        for(auto& t : X) t -= ofs;
        printf("Case #%d: %d\n", tc, solveSmall(K, X, T));
    }
}