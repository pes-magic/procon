#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FindBridge {
public:
    explicit FindBridge(const vector<vector<int>>& g) : ord(g.size(), -1), pre(g.size(), -1) {
        int curOrder = 0;
        search_(g, 0, -1, curOrder);
        auto reorder = [](vector<pair<int, int>>& v){
            for(auto& p : v){
                if(p.first > p.second) swap(p.first, p.second);
            }
            sort(v.begin(), v.end());
        };
        reorder(bridge);
        reorder(edge);
    }
private:
    void search_(const vector<vector<int>>& g, int pos, int prev, int& curOrder){
        ord[pos] = pre[pos] = curOrder;
        ++curOrder;
        for(auto& e : g[pos]){
            if(e == prev) continue;
            if(ord[e] == -1) search_(g, e, pos, curOrder);
            if(ord[pos] < pre[e]){
                bridge.emplace_back(pos, e);
            } else {
                edge.emplace_back(pos, e);
            }
            pre[pos] = min(pre[pos], pre[e]);
        }
    }
public:
    const vector<pair<int, int>> getBridge() const { return bridge; }
    const vector<pair<int, int>> getEdge() const { return edge; }
private:
    vector<int> ord;
    vector<int> pre;
    vector<pair<int, int>> bridge;
    vector<pair<int, int>> edge;
};

int main(){
    int n, m;
    while(cin >> n >> m){
        vector<vector<int>> g(n);
        for(int i=0;i<m;i++){
            int a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        FindBridge b(g);
        for(auto& e : b.getBridge()){
            cout << e.first << " " << e.second << endl;
        }
    }
}