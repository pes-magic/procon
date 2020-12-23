// 橋の検出(連結な無向グラフ)
// Verifyed
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B

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
            if(ord[e] == -1){
                search_(g, e, pos, curOrder);
                pre[pos] = min(pre[pos], pre[e]);
            } else {
                pre[pos] = min(pre[pos], ord[e]);
            }
            if(ord[pos] < pre[e]){
                bridge.emplace_back(pos, e);
            } else {
                edge.emplace_back(pos, e);
            }
        }
    }
public:
    const vector<pair<int, int>>& getBridge() const { return bridge; }
    const vector<pair<int, int>>& getEdge() const { return edge; }
private:
    vector<int> ord;
    vector<int> pre;
    vector<pair<int, int>> bridge;
    vector<pair<int, int>> edge;
};
