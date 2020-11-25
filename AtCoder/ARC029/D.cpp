#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const long long INF = (1LL << 60);

vector<long long> solve(const vector<vector<int>>& g, const vector<long long>& s, int pos){
    vector<long long> res(1, 0);
    for(auto& t : g[pos]){
        auto d = solve(g, s, t);
        int cur = res.size();
        res.resize(cur + d.size() - 1);
        for(int i=cur;i<res.size();i++) res[i] = INF;
        for(int i=cur-1;i>=0;i--){
            for(int j=1;j<d.size();j++){
                res[i+j] = min(res[i]+d[j], res[i+j]);
            }
        }
    }
    vector<long long> dp(res.size() + 1);
    dp[0] = 0;
    for(int i=0;i<res.size();i++) dp[i+1] = res[i] + s[pos];
    return dp;
}

int main(){
    int N; cin >> N;
    vector<long long> s(N);
    for(auto& v: s) cin >> v;
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        g[a-1].push_back(b-1);
    }
    auto dec = solve(g, s, 0);
    int M; cin >> M;
    vector<long long> t(M);
    for(auto& v : t) cin >> v;
    sort(t.rbegin(), t.rend());
    long long base = accumulate(s.begin(), s.end(), 0LL);
    long long sum = 0;
    long long res = 0;
    for(int i=0;i<=N;i++){
        res = max(base - dec[i] + sum, res);
        if(i >= M) break;
        sum += t[i];
    }
    cout << res << endl;
}