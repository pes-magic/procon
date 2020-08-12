#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

template<int char_size, int base>
class PMA {
public:
    explicit PMA(const vector<string>& pattern){ build_(pattern); }
    vector<vector<int>> match(const string& s) const {
        vector<vector<int>> res(s.size());
        int pos = 0;
        for(int i=0;i<s.size();i++){
            int b = s[i] - base;
            while(node[pos].next[b] == -1) pos = node[pos].fail;
            pos = node[pos].next[b];
            copy(node[pos].accept.begin(), node[pos].accept.end(), back_inserter(res[i]));
        }
        return res;
    }
private:
    void build_(const vector<string>& pattern){
        node.emplace_back();
        for(int i=0;i<pattern.size();i++){
            int nodeId = 0;
            for(const auto& c : pattern[i]){
                int b = c - base;
                int& nextId = node[nodeId].next[b];
                if(nextId == -1){
                    nextId = node.size();
                    node.emplace_back(Node());
                }
                nodeId = nextId;
            }
            node[nodeId].accept.push_back(i);
        }
        queue<int> qu;
        for(int i=0;i<char_size;i++){
            if(node[0].next[i] == -1){
                node[0].next[i] = 0;
            } else {
                qu.push(node[0].next[i]);
            }
        }
        while(!qu.empty()){
            int cur = qu.front(); qu.pop();
            const auto& preAc = node[node[cur].fail].accept;
            copy(preAc.begin(), preAc.end(), back_inserter(node[cur].accept));
            for(int i=0;i<char_size;i++){
                int next = node[cur].next[i];
                if(next == -1) continue;
                int nxt = node[cur].fail;
                while(node[nxt].next[i] == -1) nxt = node[nxt].fail;
                node[node[cur].next[i]].fail = node[nxt].next[i];
                qu.push(node[cur].next[i]);
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
};

int main(){
    string S; cin >> S;
    int M; cin >> M;
    vector<string> C(M);
    for(auto& c : C) cin >> c;
    PMA<26, 'A'> pma(C);
    auto m = pma.match(S);
    int res = 0;
    for(auto& v : m) res += v.size();
    cout << res << endl;
}