#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class UnionFind {
public:
    explicit UnionFind(int N) : root(N, -1), size(N, 1) {}
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    int getSize(int u){ return size[getRoot(u)]; }
    bool same(int a, int b){
        return getRoot(a) == getRoot(b);
    }
    bool merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u == v) return false;
        root[u] = v;
        size[v] += size[u];
        return true;
    }
private:
    vector<int> root;
    vector<int> size;
};

int solve(const string& S, int K){
    vector<pair<int, int>> seg;
    seg.emplace_back(0, S.size());
    UnionFind uf(S.size());
    for(int k=K;k>0;k--){
        vector<pair<int, int>> next;
        for(auto& p : seg){
            if(p.first == p.second) return -1;
            for(int i=0;i+p.first<p.second-1-i;i++){
                uf.merge(i+p.first, p.second-1-i);
            }
            int mid = (p.first + p.second)/2;
            next.emplace_back(p.first, mid);
            next.emplace_back(mid+(p.second-p.first)%2, p.second);
        }
        seg = next;
    }
    if(seg.front().second - seg.front().first == 1) return -1;
    vector<vector<int>> cnt(S.size(), vector<int>(26, 0));
    for(int i=0;i<S.size();i++){
        cnt[uf.getRoot(i)][S[i]-'a']++;
    }
    string T = S;
    int res = 0;
    int sub = 1000000000;
    vector<int> checked(S.size(), 0);
    for(int i=0;i<S.size();i++){
        if(checked[uf.getRoot(i)]) continue;
        checked[uf.getRoot(i)] = 1;
        int minIdx = 0, minCost = (1<<30), minCost2 = (1<<30);
        for(int j=0;j<26;j++){
            cnt[i][j] = uf.getSize(i) - cnt[uf.getRoot(i)][j];
            if(cnt[i][j] < minCost){
                minIdx = j;
                minCost2 = minCost;
                minCost = cnt[i][j];
            } else if(cnt[i][j] < minCost2){
                minCost2 = cnt[i][j];
            }
        }
        T[i] = 'a' + minIdx;
        res += minCost;
        if(i < seg.front().second && ((seg.front().second-seg.front().first)%2 == 0 || (seg.front().first+seg.front().second)/2 != i)){
            sub = min(sub, minCost2 - minCost);
        }
    }
    bool ok = (seg.front().second == 0);
    for(int i=0;i<seg.front().second-1-i;i++){
        if(T[i] != T[seg.front().second-1-i]) ok = true;
    }
    return ok ? res : res + sub;
}

int main(){
    int K; cin >> K;
    string S; cin >> S;
    int res = solve(S, K);
    if(res == -1){
        cout << "impossible" << endl;
    } else {
        cout << res << endl;
    }
}