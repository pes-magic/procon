#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FindArticulation {
public:
    explicit FindArticulation(const vector<vector<int>>& g) : ord(g.size(), -1), pre(g.size(), -1) {
        int curOrder = 0;
        search_(g, 0, -1, curOrder);
        sort(point.begin(), point.end());
    }
private:
    void search_(const vector<vector<int>>& g, int pos, int prev, int& curOrder){
        ord[pos] = pre[pos] = curOrder;
        ++curOrder;
        int deg = 0;
        bool ok = false;
        for(auto& e : g[pos]){
            if(e == prev) continue;
            if(ord[e] == -1){
                search_(g, e, pos, curOrder);
                ++deg;
                if(prev != -1 && ord[pos] <= pre[e]) ok = true;
                pre[pos] = min(pre[pos], pre[e]);
            } else {
                pre[pos] = min(pre[pos], ord[e]);
            }
        }
        if(prev == -1 && deg >= 2) ok = true;
        if(ok) point.push_back(pos);
    }
public:
    const vector<int>& get() const { return point; }
private:
    vector<int> ord;
    vector<int> pre;
    vector<int> point;
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
        FindArticulation a(g);
        for(auto& t : a.get()) cout << t << endl;
    }
}