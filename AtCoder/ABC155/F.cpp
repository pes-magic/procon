#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool dfs(int pos, const vector<vector<pair<int, int>>>& g, const vector<int>& state, vector<int>& check, vector<int>& res){
    if(check[pos]) return false;
    check[pos] = 1;
    int cnt = state[pos];
    for(auto& p : g[pos]){
        if(dfs(p.first, g, state, check, res)){
            cnt = 1 - cnt;
            res.push_back(p.second);
        }
    }
    return cnt == 1;
}

vector<int> solve(int M, const vector<pair<int,int>>& bomb){
    const int N = bomb.size();
    vector<int> cur(N+1, 0);
    cur[0] = bomb[0].second;
    for(int i=1;i<N;i++){
        cur[i] = (bomb[i].second == bomb[i-1].second ? 0 : 1);
    }
    cur[N] = bomb.back().second;
    vector<vector<pair<int,int>>> g(N+1);
    for(int i=0;i<M;i++){
        int L, R; cin >> L >> R;
        if(R < bomb[0].first || bomb.back().first < L) continue;
        int a = distance(bomb.begin(), lower_bound(bomb.begin(), bomb.end(), make_pair(L, 0)));
        int b = distance(bomb.begin(), upper_bound(bomb.begin(), bomb.end(), make_pair(R, 1)));
        g[a].emplace_back(b, i+1);
        g[b].emplace_back(a, i+1);
    }
    vector<int> res;
    vector<int> check(N+1, 0);
    for(int i=0;i<=N;i++){
        if(check[i]) continue;
        if(dfs(i, g, cur, check, res)) return vector<int>();
    }
    sort(res.begin(), res.end());
    return res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<pair<int, int>> bomb(N);
        for(auto& p : bomb) cin >> p.first >> p.second;
        sort(bomb.begin(), bomb.end());
        if(all_of(bomb.begin(), bomb.end(), [](pair<int,int>& p){ return p.second == 0; })){
            int L, R;
            for(int i=0;i<M;i++) cin >> L >> R;
            cout << 0 << endl << endl;
            continue;
        }
        auto res = solve(M, bomb);
        if(res.empty()){
            cout << -1 << endl;
        } else {
            cout << res.size() << endl;
            cout << res[0];
            for(int i=1;i<res.size();i++) cout << " " << res[i];
            cout << endl;
        }
    }
}