#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int MOD = 1000000007;

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
                    node.emplace_back();
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
                node[next].fail = node[nxt].next[i];
                qu.push(next);
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
    int N; cin >> N;
    vector<string> pattern(N);
    string S;
    for(auto& s : pattern) cin >> s;
    cin >> S;
    PMA<'a', 26> pma(pattern);
    vector<long long> dp(S.size()+1, 0);
    dp[0] = 1;
    auto m = pma.match(S);
    for(int i=1;i<=S.size();i++){
        for(auto& t : m[i-1]){
            dp[i] = (dp[i] + dp[i-pattern[t].size()]) % MOD;
        }
    }
    cout << dp.back() << endl;
}