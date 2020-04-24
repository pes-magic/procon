#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve(const vector<vector<int>>& g){
    if(any_of(g.begin(), g.end(), [](auto& v){ return v.size()%2 == 1; })) return false;
    const int N = g.size();
    vector<int> four;
    for(int i=0;i<N;i++){
        if(g[i].size() >= 6) return true;
        if(g[i].size() == 4) four.push_back(i);
    }
    if(four.size() != 2) return four.size() >= 3;
    for(auto& t : g[four[0]]){
        int pre = four[0];
        int cur = t;
        while(g[cur].size() == 2){
            int tmp = cur;
            cur = (g[cur][0] == pre ? g[cur][1] : g[cur][0]);
            pre = tmp;
        }
        if(cur == four[0]) return true;
    }
    return false;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<int>> g(N);
        for(int i=0;i<M;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        cout << (solve(g) ? "Yes" : "No") << endl;
    }
}