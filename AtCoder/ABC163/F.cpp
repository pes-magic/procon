#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

long long search(const vector<vector<int>>& g, const vector<int>& col, int pos, int prev,
                                      vector<long long>& dec,
                                      vector<map<int, long long>>& mp,
                                      vector<int>& ref)
{
    int cnt = 1;
    for(auto t : g[pos]){
        if(t == prev) continue;
        auto res = search(g, col, t, pos, dec, mp, ref);
        auto& oppMp = mp[ref[t]];
        auto num = res;
        if(oppMp.count(col[pos])) num -= oppMp[col[pos]];
        dec[col[pos]] += num * (num + 1) / 2;
        if(mp[ref[pos]].size() < mp[ref[t]].size()) swap(ref[pos], ref[t]);
        for(auto& it : mp[ref[t]]){
            if(!mp[ref[pos]].count(it.first)) mp[ref[pos]][it.first] = 0;
            mp[ref[pos]][it.first] += it.second;
        }
        cnt += res;
    }
    mp[ref[pos]][col[pos]] = cnt;
    if(prev == -1){
        for(int i=0;i<dec.size();i++){
            long long num = dec.size();
            if(mp[ref[pos]].count(i)) num -= mp[ref[pos]][i];
            dec[i] += num * (num + 1) / 2;
        }
    }
    return cnt;
}

int main(){
    long long N; cin >> N;
    vector<int> c(N);
    for(auto& t : c){ cin >> t; --t; }
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<long long> dec(N, 0);
    vector<map<int, long long>> mp(N);
    vector<int> ref(N);
    for(int i=0;i<N;i++) ref[i] = i;
    search(g, c, 0, -1, dec, mp, ref);
    for(int i=0;i<N;i++){
        cout << N*(N+1)/2 - dec[i] << endl;
    }
}