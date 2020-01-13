// 木の重心
// Verifyed
// https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_d

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
