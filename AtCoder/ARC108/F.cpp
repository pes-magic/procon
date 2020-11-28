#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

vector<int> calcDist(const vector<vector<int>>& g, int start){
    const int N = g.size();
    vector<int> res(N, -1);
    res[start] = 0;
    queue<int> qu; qu.push(start);
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(auto& t : g[p]){
            if(res[t] != -1) continue;
            res[t] = res[p] + 1;
            qu.push(t);
        }
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    auto d0 = calcDist(g, 0);
    int idx0 = distance(d0.begin(), max_element(d0.begin(), d0.end()));
    auto d1 = calcDist(g, idx0);
    int idx1 = distance(d1.begin(), max_element(d1.begin(), d1.end()));
    auto d2 = calcDist(g, idx1);
    int dia = *max_element(d2.begin(), d2.end());
    vector<long long> p2(N+1);
    p2[0] = 1;
    for(int i=1;i<=N;i++) p2[i] = (2*p2[i-1]) % MOD;
    long long res = p2[N-1] * dia % MOD;
    vector<int> num(dia+1), mins(dia+1, 0);
    for(int i=0;i<N;i++){
        if(i == idx0 || i == idx1) continue;
        int m = min(d1[i], d2[i]);
        int M = max(d1[i], d2[i]);
        num[M]++;
        mins[M] = max(mins[M], m);
    }
    int numSum = 0, lower = 0;
    for(int i=dia;i>=0;i--){
        if(lower > i) break;
        if(lower == i){
            res = (res + p2[N-numSum-1] * i) % MOD;
        } else {
            auto p = p2[num[i]];
            if(mins[i] < i) p = (p+MOD-1) % MOD;
            res = (res + p * p2[N-numSum-1-num[i]] % MOD * i) % MOD;
        }
        numSum += num[i];
        lower = max(lower, mins[i]);
    }
    cout << res << endl;
}