#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

template<int char_size, int base>
class PMA {
public:
    explicit PMA(const vector<string>& pattern, long long X, long long Y){ build_(pattern, X, Y); }
    long long solve(const string& s, long long X, long long Y) const {
        long long res = (X+Y) * node.size();
        int pos = 0;
        for(int i=0;i<s.size();i++){
            int b = s[i] - base;
            while(node[pos].next[b] == -1) pos = node[pos].fail;
            pos = node[pos].next[b];
            res = min<long long>(res,  s.size() * X + cost[pos]);
        }
        return res;
    }
private:
    void build_(const vector<string>& pattern, long long X, long long Y){
        node.emplace_back();
        for(int i=0;i<pattern.size();i++){
            int nodeId = 0;
            for(const auto& c : pattern[i]){
                int b = c - base;
                int& nextId = node[nodeId].next[b];
                if(nextId == -1){
                    nextId = node.size();
                    node.emplace_back();
                }
                nodeId = nextId;
            }
            node[nodeId].accept.push_back(i);
        }
        vector<int> depth(node.size(), 0);
        vector<int> rest(node.size(), 0);
        queue<int> qu;
        for(int i=0;i<char_size;i++){
            if(node[0].next[i] == -1){
                node[0].next[i] = 0;
            } else {
                depth[node[0].next[i]] = 1;
                qu.push(node[0].next[i]);
            }
        }
        while(!qu.empty()){
            int cur = qu.front(); qu.pop();
            for(int i=0;i<char_size;i++){
                int next = node[cur].next[i];
                if(next == -1) continue;
                int nxt = node[cur].fail;
                while(node[nxt].next[i] == -1) nxt = node[nxt].fail;
                depth[next] = depth[cur] + 1;
                node[next].fail = node[nxt].next[i];
                qu.push(next);
            }
        }
        auto calcRest = [&](auto f, int pos) -> int {
            rest[pos] = node.size();
            if(!node[pos].accept.empty()) rest[pos] = 0;
            for(auto next : node[pos].next){
                if(next <= 0) continue;
                rest[pos] = min(rest[pos], f(f, next)+1);
            }
            return rest[pos];
        };
        calcRest(calcRest, 0);
        cost.assign(node.size(), 0);
        qu.push(0);
        while(!qu.empty()){
            int cur = qu.front(); qu.pop();
            cost[cur] = rest[cur] * Y - depth[cur] * X;
            cost[cur] = min(cost[node[cur].fail], cost[cur]);
            for(auto& next : node[cur].next){
                if(next > 0) qu.push(next);
            }
        }
    }
private:
    struct Node {
        vector<int> next;
        vector<int> accept;
        int fail;
        Node() : next(char_size, -1), fail(0) {}
    };
    vector<Node> node;
    vector<long long> cost;
};

int main(){
    int N, Q, X, Y; cin >> N >> Q >> X >> Y;
    vector<string> S(N);
    for(auto& s : S) cin >> s;
    PMA<26, 'a'> pma(S, X, Y);
    for(int i=0;i<Q;i++){
        string T; cin >> T;
        cout << pma.solve(T, X, Y) << endl;
    }

}