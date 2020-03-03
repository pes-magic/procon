#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool solve(int R, int C){
    vector<vector<pair<int, int>>> gr(R), gc(C);
    int N; cin >> N;
    for(int i=0;i<N;i++){
        int r, c, a; cin >> r >> c >> a;
        gr[r-1].emplace_back(c-1, a);
        gc[c-1].emplace_back(r-1, a);
    }
    vector<long long> dif(R);
    vector<int> check(R, 0);
    for(int i=0;i<R;i++){
        if(check[i]) continue;
        dif[i] = 0;
        check[i] = 1;
        long long m = 1LL << 60;
        auto md = dif[i];
        queue<int> qu; qu.push(i);
        while(!qu.empty()){
            int p = qu.front(); qu.pop();
            for(auto c : gr[p]){
                int val = c.second;
                for(auto r : gc[c.first]){
                    auto d = r.second - c.second + dif[p];
                    if(!check[r.first]){
                        check[r.first] = 1;
                        dif[r.first] = d;
                        qu.push(r.first);
                    }
                    if(dif[r.first] != d) return false;
                    md = min(d, md);
                    m = min(m, r.second - d);
                }
            }
        }
        if(m + md < 0) return false;
    }
    return true;
}

int main(){
    int R, C;
    while(cin >> R >> C){
        cout << (solve(R, C) ? "Yes" : "No") << endl;
    }
}