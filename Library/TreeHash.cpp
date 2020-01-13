// 木のハッシュ
// Verifyed
// https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_d

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
