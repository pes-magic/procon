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
#include <queue>
#include <numeric>
#include <map>


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
pair<vector<int>, vector<vector<int>>> initial_separate(const vector<vector<int>>& coord_x, int num_y, int x_sep, int y_sep){
    vector<int> cnt(15);
    vector<vector<int>> coord(x_sep, vector<int>(y_sep, 0));
    int cur_x = 0;
    for(int i=0;i<x_sep;i++){
        int end_x = cur_x + (coord_x.size() + i) / x_sep;
        for(int x=cur_x;x<end_x;x++){
            int cur_y = 0;
            int cur_seg = 0;
            int end_y = cur_y + (num_y + cur_seg) / y_sep;
            for(const auto& y : coord_x[x]){
                while(y >= end_y){
                    ++cur_seg;
                    cur_y = end_y;
                    end_y += (num_y + cur_seg) / y_sep;
                }
                coord[i][cur_seg]++;
            }
        }
        cur_x = end_x;
        for(int j=0;j<y_sep;j++){
            ++cnt[min(14, coord[i][j])];
        }
    }
    return {cnt, coord};
}

//------------------------------------------------------------------------------
int main(){
    Timer timer;
    const double initial_temp = 10.1;
    const double final_temp = 0.1;
    std::ios::sync_with_stdio(false);
    int N, K; cin >> N >> K;
    vector<int> a(11, 0);
    for(int i=1;i<=10;i++) cin >> a[i];
    vector<pair<int,int>> coord(N);
    vector<int> x;
    vector<int> y;

    for(int i=0;i<N;i++){
        cin >> coord[i].first >> coord[i].second;
        x.push_back(coord[i].first);
        y.push_back(coord[i].second);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    map<int,int> xmap;
    map<int,int> ymap;
    for(int i=0;i<x.size();i++) xmap[x[i]] = i;
    for(int i=0;i<y.size();i++) ymap[y[i]] = i;
    vector<vector<int>> coord_x(x.size());
    vector<vector<int>> coord_y(y.size());
    for(int i=0;i<N;i++){
        coord_x[xmap[coord[i].first]].push_back(ymap[coord[i].second]);
        coord_y[ymap[coord[i].second]].push_back(xmap[coord[i].first]);
    }
    for(auto& v : coord_x) sort(v.begin(), v.end());
    for(auto& v : coord_y) sort(v.begin(), v.end());
    int x_sep = 1;
    int y_sep = 1;
    int best_score = 0;
    vector<int> best_cnt;
    vector<vector<int>> best_coord;
    for(int i=1;i<=K+1;i++){
        for(int j=1;i+j<=K+2;j++){
            if(i != 10 && j != 90) continue;
            auto [cnt, coord] = initial_separate(coord_x, coord_y.size(), i, j);
            double score = 0;
            for(int k=1;k<=10;k++){
                score += min(cnt[k], a[k]);
            }
            if(score > best_score){
                best_score = score;
                best_cnt = cnt;
                best_coord = coord;
                x_sep = i;
                y_sep = j;
            }
        }
    }
    vector<int> cut_x(x_sep+1);
    vector<int> cut_y(y_sep+1);
    cut_x[0] = 0;
    cut_y[0] = 0;
    for(int i=0;i<x_sep;i++){
        cut_x[i+1] = cut_x[i] + (coord_x.size() + i) / x_sep;
    }
    for(int i=0;i<y_sep;i++){
        cut_y[i+1] = cut_y[i] + (coord_y.size() + i) / y_sep;
    }
    if(cut_x.size() == 2 && cut_y.size() == 2){
        cout << 0 << endl;
        return 0;
    }

    int sum_a = 0;
    for(int i=1;i<=10;i++) sum_a += a[i];

    double cur_time = timer.msec();
    const double start_time = cur_time;
    const double time_limit = 1950;
    auto cur_coord = best_coord;
    auto cur_cnt = best_cnt;
    auto cur_score = best_score;
    cerr << (double)cur_score/sum_a << endl;
    // XorShift rnd(chrono::steady_clock::now().time_since_epoch().count());
    XorShift rnd(1234567890);
    auto best_cut_x = cut_x;
    auto best_cut_y = cut_y;
    while(cur_time < time_limit){
        int r = rnd() % (cut_x.size() + cut_y.size() - 4);
        int move_x = r < cut_x.size() - 2;
        if(r >= cut_x.size() - 2) r -= cut_x.size() - 2;
        ++r;
        int move_num = rnd() % 6 - 2;
        if(move_num <= 0) --move_num;
        if(move_num > 0){
            if(move_x){
                while(cut_x[r] + move_num >= cut_x[r+1]) --move_num;
            } else {
                while(cut_y[r] + move_num >= cut_y[r+1]) --move_num;
            }
        } else {
            if(move_x){
                while(cut_x[r] + move_num <= cut_x[r-1]) ++move_num;
            } else {
                while(cut_y[r] + move_num <= cut_y[r-1]) ++move_num;
            }
        }
        if(move_num == 0) continue;
        if(move_x){
            int sx = min(cut_x[r], cut_x[r]+move_num);
            int ex = max(cut_x[r], cut_x[r]+move_num);
            for(int x=sx;x<ex;x++){
                int seg_y = 0;
                for(const auto& y : coord_x[x]){
                    while(y >= cut_y[seg_y+1]){
                        ++seg_y;
                    }
                    --cur_cnt[min(14, cur_coord[r-1][seg_y])];
                    --cur_cnt[min(14, cur_coord[r][seg_y])];
                    if(move_num < 0){
                        cur_coord[r-1][seg_y]--;
                        cur_coord[r][seg_y]++;
                    } else {
                        cur_coord[r-1][seg_y]++;
                        cur_coord[r][seg_y]--;
                    }
                    ++cur_cnt[min(14, cur_coord[r-1][seg_y])];
                    ++cur_cnt[min(14, cur_coord[r][seg_y])];
                }
            }
        } else {
            int sy = min(cut_y[r], cut_y[r]+move_num);
            int ey = max(cut_y[r], cut_y[r]+move_num);
            for(int y=sy;y<ey;y++){
                int seg_x = 0;
                for(const auto& x : coord_y[y]){
                    while(x >= cut_x[seg_x+1]){
                        ++seg_x;
                    }
                    --cur_cnt[min(14, cur_coord[seg_x][r-1])];
                    --cur_cnt[min(14, cur_coord[seg_x][r])];
                    if(move_num < 0){
                        cur_coord[seg_x][r-1]--;
                        cur_coord[seg_x][r]++;
                    } else {
                        cur_coord[seg_x][r-1]++;
                        cur_coord[seg_x][r]--;
                    }
                    ++cur_cnt[min(14, cur_coord[seg_x][r-1])];
                    ++cur_cnt[min(14, cur_coord[seg_x][r])];
                }
            }
        }
        int new_score = 0;
        for(int k=1;k<=10;k++){
            new_score += min(cur_cnt[k], a[k]);
        }
        double ratio = (cur_time - start_time) / (time_limit - start_time);
        double temp = initial_temp + (final_temp - initial_temp) * ratio;
        if(new_score >= cur_score || std::bernoulli_distribution((new_score - cur_score) / temp)(rnd)){
            if(move_x){
                cut_x[r] += move_num;
            } else {
                cut_y[r] += move_num;
            }
            cur_score = new_score;
            if(new_score > best_score){
                best_score = new_score;
                best_cut_x = cut_x;
                best_cut_y = cut_y;
                best_cnt = cur_cnt;
            }
        } else {
            if(move_x){
                int sx = min(cut_x[r], cut_x[r]+move_num);
                int ex = max(cut_x[r], cut_x[r]+move_num);
                for(int x=sx;x<ex;x++){
                    int seg_y = 0;
                    for(const auto& y : coord_x[x]){
                        while(y >= cut_y[seg_y+1]){
                            ++seg_y;
                        }
                        --cur_cnt[min(14, cur_coord[r-1][seg_y])];
                        --cur_cnt[min(14, cur_coord[r][seg_y])];
                        if(move_num < 0){
                            cur_coord[r-1][seg_y]++;
                            cur_coord[r][seg_y]--;
                        } else {
                            cur_coord[r-1][seg_y]--;
                            cur_coord[r][seg_y]++;
                        }
                        ++cur_cnt[min(14, cur_coord[r-1][seg_y])];
                        ++cur_cnt[min(14, cur_coord[r][seg_y])];
                    }
                }
            } else {
                int sy = min(cut_y[r], cut_y[r]+move_num);
                int ey = max(cut_y[r], cut_y[r]+move_num);
                for(int y=sy;y<ey;y++){
                    int seg_x = 0;
                    for(const auto& x : coord_y[y]){
                        while(x >= cut_x[seg_x+1]){
                            ++seg_x;
                        }
                        --cur_cnt[min(14, cur_coord[seg_x][r-1])];
                        --cur_cnt[min(14, cur_coord[seg_x][r])];
                        if(move_num < 0){
                            cur_coord[seg_x][r-1]++;
                            cur_coord[seg_x][r]--;
                        } else {
                            cur_coord[seg_x][r-1]--;
                            cur_coord[seg_x][r]++;
                        }
                        ++cur_cnt[min(14, cur_coord[seg_x][r-1])];
                        ++cur_cnt[min(14, cur_coord[seg_x][r])];
                    }
                }
            }
        }
        cur_time = timer.msec();
    }
    cerr << (double)cur_score/sum_a << endl;
    cerr << (double)best_score/sum_a << endl;

    for(int i=1;i<=10;i++) cerr << i << ": " << a[i] << " " << best_cnt[i] << endl;

    cout << cut_x.size() - 2 + cut_y.size() - 2 << endl;
    for(int i=1;i<cut_x.size()-1;i++){
        cout << x[best_cut_x[i]]-1 << " " << -1000000 << " " << x[best_cut_x[i]] << " " << 1000000 << endl;
    }
    for(int i=1;i<cut_y.size()-1;i++){
        cout << -1000000 << " " << y[best_cut_y[i]]-1 << " " << 1000000 << " " << y[best_cut_y[i]] << endl;
    }
}