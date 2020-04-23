#include <iostream>
#include <vector>
#include <functional>

using namespace std;

vector<int> treeCentroid(const vector<vector<pair<int, long long>>>& g){
    vector<int> res;
    function<int(int, int)> dfs = [&](int pos, int prev){
        int size = 1;
        int maxSize = 0;
        for(auto& t : g[pos]){
            if(t.first == prev) continue;
            int cur = dfs(t.first, pos);
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

pair<int, long long> solve(const vector<vector<pair<int, long long>>>& g, int pos, int prev){
    int num = 1;
    long long cost = 0;
    long long back = 0;
    for(auto& t : g[pos]){
        if(t.first == prev){
            back = t.second;
        } else {
            auto pr = solve(g, t.first, pos);
            num += pr.first;
            cost += pr.second;
        }
    }
    cost += 2 * num * back;
    return make_pair(num, cost);
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<pair<int, long long>>> g(N);
        for(int i=0;i<N-1;i++){
            int A, B;
            long long C;
            cin >> A >> B >> C;
            g[A-1].emplace_back(B-1, C);
            g[B-1].emplace_back(A-1, C);
        }
        auto centroid = treeCentroid(g);
        long long res = solve(g, centroid[0], -1).second;
        long long dec = 1LL << 40;
        for(auto& t : g[centroid[0]]){
            if(centroid.size() == 2 && t.first == centroid[1]){
                dec = t.second;
                break;
            } else {
                dec = min(dec, t.second);
            }
        }
        cout << res - dec << endl;
    }
}