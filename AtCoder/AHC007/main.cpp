#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <limits>
#include <cassert>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;

//------------------------------------------------------------------------------
class Timer {
public:
    explicit Timer()
        : mStart(chrono::system_clock::now())
    {}
    void start() { mStart = chrono::system_clock::now(); }
    double msec() const {
        auto t = chrono::system_clock::now();
        return 1e-3 * chrono::duration_cast<std::chrono::microseconds>(t - mStart).count();
    }
private:
    chrono::system_clock::time_point mStart;
};

//------------------------------------------------------------------------------
class XorShift {
public:
    using result_type = uint32_t;
    explicit XorShift(result_type seed){ init(seed); }
    void init(result_type s){
        x = 1812433253U * (s ^ (s >> 30));
        y = 1812433253U * (x ^ (x >> 30)) + 1;
        z = 1812433253U * (y ^ (y >> 30)) + 2;
        w = 1812433253U * (z ^ (z >> 30)) + 3;
    }
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    result_type operator() () {
        result_type t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    // a <= x <= b の一様乱数を生成
    result_type random_range(result_type a, result_type b) {
        result_type random_value = (*this)();
        return a + (random_value % (b - a + 1));
    }
private:
    result_type x;
    result_type y;
    result_type z;
    result_type w;
};

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
int main(){
    Timer timer;
    const int N = 400;
    const int M = 1995;
    vector<pair<int,int>> coord(N);
    vector<pair<int,int>> edge(M);
    for(auto& p : coord) cin >> p.first >> p.second;
    for(auto& p : edge) cin >> p.first >> p.second;
    vector<int> d(M);
    for(int i=0;i<M;i++){
        auto [x0, y0] = coord[edge[i].first];
        auto [x1, y1] = coord[edge[i].second];
        int dx = x1 - x0;
        int dy = y1 - y0;
        d[i] = (int)(sqrt(dx*dx + dy*dy) + 0.5);
    }
    vector<bool> used(M, false);

    XorShift rnd(chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distr(1.0, 3.0);
    const int max_rep_num = 100;
    vector<vector<pair<int, int>>> edge_costs(max_rep_num, vector<pair<int, int>>(M));
    for(int i=0;i<max_rep_num;i++){
        for(int j=0;j<M;j++){
            edge_costs[i][j] = {int(d[j] * distr(rnd)), j};
        }
        sort(edge_costs[i].begin(), edge_costs[i].end());
    }

    for(int i=0;i<M;i++){
        int len; cin >> len;
        UnionFind base_uf1(N);
        UnionFind base_uf2(N);
        int base_cnt = 0;
        for(int j=0;j<i;j++){
            if(used[j]){
                base_uf1.merge(edge[j].first, edge[j].second);
                base_uf2.merge(edge[j].first, edge[j].second);
                ++base_cnt;
            }
        }
        bool ok = base_uf1.merge(edge[i].first, edge[i].second);
        const double cur_time = timer.msec();
        double time_limit = (1950 - cur_time) / (M-i) + cur_time;
        int cost1 = 0, cost2 = 0;
        bool first = true;
        for(const auto& costs: edge_costs){
            if(!ok) break;
            if(!first && timer.msec() > time_limit) break;
            auto uf1 = base_uf1;
            auto uf2 = base_uf2;
            cost1 += len;
            int cnt = base_cnt;
            for (const auto& [c, j] : costs){
                if(j <= i) continue;
                if(uf1.merge(edge[j].first, edge[j].second)){
                    cost1 += c;
                }
                if(uf2.merge(edge[j].first, edge[j].second)){
                    cost2 += c;
                    ++cnt;
                    if(cnt == N-1) break;
                }
            }
            if(first && cnt != N-1){
                cost2 = numeric_limits<int>::max();
                break;
            }
            first = false;
        }
        if(ok && cost1 < cost2){
            used[i] = true;
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
}