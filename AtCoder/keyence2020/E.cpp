#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Node {
public:
    explicit Node(int dst = 0, int idx = -1) : dst(dst), idx(idx) {}
    int dst, idx;
};

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<Node>> g(N);
        vector<int> D(N);
        for(auto& t : D) cin >> t;
        vector<pair<int,int>> d;
        for(int i=0;i<N;i++){
            d.emplace_back(D[i], i);
        }
        for(int i=0;i<M;i++){
            int U, V; cin >> U >> V;
            --U; --V;
            g[U].emplace_back(V, i);
            g[V].emplace_back(U, i);
        }
        sort(d.begin(), d.end());
        string res(N, '?');
        vector<long long> cost(M, -1);
        vector<int> state(N, 0);
        for(int i=0;i<N;i++){
            for(auto& e : g[d[i].second]){
                if(res[d[i].second] != '?') break;
                int pos = e.dst;
                if(D[pos] < d[i].first){
                    if(res[pos] != '?'){
                        res[d[i].second] = res[pos];
                        cost[e.idx] = d[i].first - D[pos];
                    }
                } else if(D[pos] == d[i].first){
                    cost[e.idx] = D[pos];
                    if(res[pos] != '?'){
                        res[d[i].second] = (res[pos] == 'W' ? 'B' : 'W');
                    } else {
                        res[d[i].second] = 'W';
                        res[pos] = 'B';
                    }
                }
            }
        }
        if(res.find('?') == string::npos){
            cout << res << endl;
            for(auto& t : cost) cout << (t == -1 ? 1000000000 : t) << endl;
        } else {
            cout << -1 << endl;
        }
    }
}