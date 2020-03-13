#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> getDist(const vector<vector<int>>& g, int start){
    const int n = g.size();
    vector<int> res(n, -1);
    queue<int> qu; qu.push(start);
    res[start] = 0;
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

long long check(const vector<vector<int>>& g, const vector<int>& start){
    auto cur = start;
    vector<int> check(g.size(), 0);
    for(auto& t : cur) check[t] = 1;
    long long res = 0;
    while(!cur.empty()){
        int maxDeg = 1;
        for(auto& t : cur) maxDeg = max<int>(maxDeg, g[t].size()-1);
        res *= maxDeg;
        vector<int> next;
        for(auto& t : cur){
            res += maxDeg - (g[t].size() - 1);
            for(auto& p : g[t]){
                if(check[p]) continue;
                check[p] = 1;
                next.push_back(p);
            }
        }
        cur = next;
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> g(N);
        for(int i=0;i<N-1;i++){
            int a, b; cin >> a >> b;
            g[a-1].push_back(b-1);
            g[b-1].push_back(a-1);
        }
        auto d = getDist(g, 0);
        int s = distance(d.begin(), max_element(d.begin(), d.end()));
        d = getDist(g, s);
        s = distance(d.begin(), max_element(d.begin(), d.end()));
        vector<int> cur;
        const int maxD = d[s];
        const int color = (maxD+2)/2;
        while(true){
            if(min(d[s], maxD - d[s]) == color-1){
                cur.push_back(s);
            }
            if(d[s] == 0) break;
            for(auto& t : g[s]){
                if(d[t] + 1 == d[s]){
                    s = t;
                    break;
                }
            }
        }
        long long res = check(g, cur);
        if(cur.size() == 1){
            for(auto& t : g[cur[0]]){
                vector<int> start = {cur[0], t};
                res = min(res, check(g, start));
            }
        }
        cout << color << " " << res << endl;
    }
}