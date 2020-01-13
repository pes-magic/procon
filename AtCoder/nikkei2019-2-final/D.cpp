#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> treeCentroid(const vector<vector<int>>& g){
    vector<int> res;
    function<int(int, int)> dfs = [&](int pos, int prev){
        int size = 1;
        int maxSize = 0;
        for(auto& t : g[pos]){
            if(t == prev) continue;
            int cur = dfs(t, pos);
            size += cur;
            maxSize = max(maxSize, cur);
        }
        maxSize = max<int>(maxSize, g.size() - size);
        if(2*maxSize <= g.size()) res.push_back(pos);
        return size;
    };
    dfs(0, -1);
    return res;
}

class TreeHash {
public:
    explicit TreeHash() : hashedVec(1, vector<int>()) { hash[vector<int>()] = 0; }
    vector<int> get(const vector<vector<int>>& g, int s){
        vector<int> res(g.size());
        search(g, s, -1, res);
        return res;
    }
    const auto getVec(int h) const { return hashedVec[h]; }
private:
    int search(const vector<vector<int>>& g, int pos, int prev, vector<int>& mem){
        vector<int> v;
        for(auto& t : g[pos]){
            if(t == prev) continue;
            v.push_back(search(g, t, pos, mem));
        }
        sort(v.begin(), v.end());
        if(!hash.count(v)){
            hash[v] = hashedVec.size();
            hashedVec.push_back(v);
        }
        return mem[pos] = hash[v];
    }
    vector<vector<int>> hashedVec;
    map<vector<int>, int> hash;
};

class Solver {
public:
    explicit Solver(int N) : g(N+1), h(N) {
        read(g);
        read(h);
    }
    vector<int> solve(){
        vector<int> cg = treeCentroid(g);
        vector<int> ch = treeCentroid(h);
        vector<int> res;
        for(auto& rg : cg){
            for(auto& rh : ch){
                vector<int> hashG = treeHash.get(g, rg);
                vector<int> hashH = treeHash.get(h, rh);
                dfs(rg, -1, hashG, hashH[rh], res);
            }
        }
        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());
        return res;
    }
private:
    void read(vector<vector<int>>& graph){
        for(int i=0;i<graph.size()-1;i++){
            int u; cin >> u;
            --u;
            graph[i].push_back(u);
            graph[u].push_back(i);
        }
    }
    void dfs(int pos, int prev, const vector<int>& hashG, int hashH, vector<int>& res){
        auto vecG = treeHash.getVec(hashG[pos]);
        auto vecH = treeHash.getVec(hashH);
        if(vecG.size() == vecH.size() + 1){
            vector<int> v = vecG;
            auto it = find(v.begin(), v.end(), 0);
            if(it == v.end()) return;
            v.erase(it);
            if(v != vecH) return;
            for(auto& t : g[pos]){
                if(hashG[t] == 0) res.push_back(t+1);
            }
        } else if(vecG.size() == vecH.size()){
            int idxg = 0, idxh = 0, g0 = -1, h0 = -1;
            while(idxg < vecG.size() || idxh < vecH.size()){
                if(idxg >= vecG.size()){
                    if(h0 != -1) return;
                    h0 = vecH[idxh];
                    ++idxh;
                } else if(idxh >= vecH.size()){
                    if(g0 != -1) return;
                    g0 = vecG[idxg];
                    ++idxg;
                } else if(vecG[idxg] == vecH[idxh]){
                    ++idxg;
                    ++idxh;
                } else {
                    if(vecG[idxg] < vecH[idxh]){
                        if(g0 != -1) return;
                        g0 = vecG[idxg];
                        ++idxg;
                    } else {
                        if(h0 != -1) return;
                        h0 = vecH[idxh];
                        ++idxh;
                    }
                }
            }
            if(g0 != -1 && h0 != -1){
                for(auto& t : g[pos]){
                    if(t == prev) continue;
                    if(hashG[t] == g0) dfs(t, pos, hashG, h0, res);
                }
            }
        }
    }
private:
    vector<vector<int>> g, h;
    TreeHash treeHash;
};

int main(){
    int N;
    while(cin >> N){
        Solver solver(N);
        auto res = solver.solve();
        if(res.empty()) cout << "ERROR" << endl;
        else {
            cout << res[0];
            for(int i=1;i<res.size();i++) cout << " " << res[i];
            cout << endl;
        }
    }
}