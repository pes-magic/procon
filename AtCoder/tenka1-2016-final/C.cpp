#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<int char_size, int base>
class Trie {
public:
    explicit Trie() : node(1, Node()) {}
    void insert(const string& word, int id){
        int nodeId = 0;
        for(const auto& c : word){
            int b = c - base;
            int& nextId = node[nodeId].next[b];
            if(nextId == -1){
                nextId = node.size();
                node.emplace_back(Node());
            }
            nodeId = nextId;
        }
        node[nodeId].accept.push_back(id);
    }
    vector<int> match(const string& s, int offset){
        vector<int> res;
        int nodeId = 0;
        for(int i=offset;i<s.size();i++){
            int b = s[i] - base;
            auto nextId = node[nodeId].next[b];
            if(nextId == -1) break;
            nodeId = nextId;
            for(auto& t : node[nodeId].accept) res.push_back(t);
        }
        return res;
    }
private:
    struct Node {
        vector<int> next;
        vector<int> accept;
        Node() : next(char_size, -1) {}
    };
    vector<Node> node;

};

int main(){
    string S; cin >> S;
    Trie<26, 'a'> trie;
    int M; cin >> M;
    vector<string> P(M);
    for(auto& s : P) cin >> s;
    for(int i=0;i<M;i++) trie.insert(P[i], i);
    vector<int> W(M);
    for(auto& t : W) cin >> t;
    vector<int> dp(S.size()+1, 0);
    for(int i=0;i<S.size();i++){
        dp[i+1] = max(dp[i+1], dp[i]);
        auto r = trie.match(S, i);
        for(auto& t : r){
            dp[i+P[t].size()] = max(dp[i+P[t].size()], dp[i] + W[t]);
        }
    }
    cout << dp.back() << endl;
}