#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

const double INF = 1e12;

pair<int, double> search(const vector<vector<pair<int, double>>>& g, int start){
    vector<double> unit(g.size(), INF);
    unit[start] = 1.0;
    queue<int> qu; qu.push(start);
    while(!qu.empty()){
        int pos = qu.front(); qu.pop();
        for(auto& p : g[pos]){
            if(unit[p.first] < INF) continue;
            unit[p.first] = unit[pos] * p.second;
            qu.push(p.first);
        }
    }
    auto res = make_pair(start, 1.0);
    for(int i=0;i<g.size();i++){
        if(res.second < unit[i]) res = make_pair(i, unit[i]);
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<string> names;
        map<string, int> idx;
        vector<vector<pair<int, double>>> g;
        for(int i=0;i<N;i++){
            string large, small;
            int m;
            cin >> large >> m >> small;
            if(!idx.count(large)){
                idx[large] = names.size();
                names.push_back(large);
                g.push_back(vector<pair<int, double>>());
            }
            if(!idx.count(small)){
                idx[small] = names.size();
                names.push_back(small);
                g.push_back(vector<pair<int, double>>());
            }
            g[idx[large]].emplace_back(idx[small], m);
            g[idx[small]].emplace_back(idx[large], 1.0/m);
        }
        int a, b;
        double m = 0.0;
        for(int i=0;i<names.size();i++){
            auto p = search(g, i);
            if(p.second > m){
                a = i;
                b = p.first;
                m = p.second;
            }
        }
        cout << 1 << names[a] << "=" << (int(m+0.5)) << names[b] << endl;
    }
}