#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template<int char_size, int base>
class Trie {
public:
    explicit Trie() : res(0), node(1, Node()) {}
    void insert(const string& word){
        vector<int> cnt(char_size, 0);
        for(auto& c : word) cnt[c - base]++;
        int nodeId = 0;
        for(const auto& c : word){
            for(int i=0;i<char_size;i++){
                if(cnt[i] > 0 && node[nodeId].next[i] != -1){
                    res += node[node[nodeId].next[i]].accept;
                }
            }
            int b = c - base;
            int& nextId = node[nodeId].next[b];
            if(nextId == -1){
                nextId = node.size();
                node.emplace_back(Node());
            }
            cnt[b]--;
            nodeId = nextId;
        }
        node[nodeId].accept = 1;
    }
    long long getRes() const { return res; }
private:
    long long res;
    struct Node {
        vector<int> next;
        int accept;
        Node() : next(char_size, -1), accept(0) {}
    };
    vector<Node> node;
};

int main(){
    int N; cin >> N;
    vector<string> vs(N);
    for(auto& s : vs){
        cin >> s;
        reverse(s.begin(), s.end());
    }
    sort(vs.begin(), vs.end(), [](const string& a, const string& b){ return a.size() < b.size(); });
    Trie<26, 'a'> trie;
    for(auto& s : vs){
        trie.insert(s);
    }
    cout << trie.getRes() << endl;
}