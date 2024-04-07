#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <cassert>
#include <tuple>
#include <queue>

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
private:
    result_type x;
    result_type y;
    result_type z;
    result_type w;
};

//------------------------------------------------------------------------------
int bit_count(long long t){
    t = (t & 0x5555555555555555) + (t >> 1 & 0x5555555555555555);
    t = (t & 0x3333333333333333) + (t >> 2 & 0x3333333333333333);
    t = (t & 0x0f0f0f0f0f0f0f0f) + (t >> 4 & 0x0f0f0f0f0f0f0f0f);
    t = (t & 0x00ff00ff00ff00ff) + (t >> 8 & 0x00ff00ff00ff00ff);
    t = (t & 0x0000ffff0000ffff) + (t >> 16 & 0x0000ffff0000ffff);
    t = (t & 0x00000000ffffffff) + (t >> 32 & 0x00000000ffffffff);
    return t;
}

//------------------------------------------------------------------------------
pair<vector<vector<int>>, vector<int>> merge_days(const vector<vector<int>>& a, int W){
    vector<vector<int>> ret;
    vector<pair<int, int>> dp(a.size() + 1, make_pair(a.size()+2, 0));
    dp[0] = make_pair(0, 0);
    vector<int> prev(a.size() + 1, -1);
    for(int i=0;i<a.size();i++){
        vector<int> mx = a[i];
        for(int j=i;j<a.size();j++){
            for(int k=0;k<a[j].size();k++){
                mx[k] = max(mx[k], a[j][k]);
            }
            int sum = 0;
            for(auto& t : mx){
                sum += t;
            }
            if(j != i && sum > W*W - 5000) break;
            const int next_step = dp[i].first + 1;
            const int next_cost = dp[i].second + sum;
            if(dp[j+1] > make_pair(next_step, next_cost)){
                dp[j+1] = make_pair(next_step, next_cost);
                prev[j+1] = i;
            }
        }
    }
    pair<vector<vector<int>>, vector<int>> res;
    int cur = a.size();
    while(cur > 0){
        int pre = prev[cur];
        vector<int> mx = a[pre];
        for(int i=pre;i<cur;i++){
            for(int j=0;j<a[i].size();j++){
                mx[j] = max(mx[j], a[i][j]);
            }
        }
        res.first.push_back(mx);
        res.second.push_back(cur - pre);
        cur = pre;
    }
    reverse(res.first.begin(), res.first.end());
    reverse(res.second.begin(), res.second.end());
    return res;
}

//------------------------------------------------------------------------------
pair<long long, vector<vector<vector<int>>>> calc_partition_cost(
    int W,
    const vector<vector<int>>& a,
    const vector<int>& width,
    const vector<vector<vector<int>>>& cur_assign)
{
    long long new_cost = 0;
    // cerr << "called" << endl;
    // cerr << "Width: " << width.size() << endl;
    vector<vector<vector<int>>> new_assign(a.size(), vector<vector<int>>(width.size(), vector<int>()));
    for(int i=0;i<a.size();i++){
        priority_queue<pair<int, int>> qu;
        vector<int> used(cur_assign[i].size(), 0);
        vector<int> cur_height(width.size(), 0);
        vector<int> cur_assign_idx(a[i].size(), -1);
        for(int j=0;j<cur_assign[i].size();j++){
            for(int k=0;k<cur_assign[i][j].size();k++){
                cur_assign_idx[cur_assign[i][j][k]] = j;
            }
            if(!cur_assign[i][j].empty()){
                qu.push(make_pair(a[i][cur_assign[i][j][0]], cur_assign[i][j][0]));
                used[j] += 1;
            }
            for(int k=1;k<cur_assign[i][j].size();k++){
                if(width.size() <= j || width[j] == 0){
                    qu.push(make_pair(a[i][cur_assign[i][j][k]], cur_assign[i][j][k]));
                    used[j] += 1;
                } else {
                    cur_height[j] += (a[i][cur_assign[i][j][k]] + width[j] - 1) / width[j];
                }
            }
        }
        // for(auto& u : used) cerr << u << " "; cerr << endl;
        // cerr << "qu" << endl;
        while(!qu.empty()){
            auto [value, idx] = qu.top(); qu.pop();
            // cerr << "pop:" << value << " " << idx << endl;
            const int assign_idx = cur_assign_idx[idx];
            // cerr << "assign_idx = " << assign_idx << ", used = " << used[assign_idx] << ", cur_assign_size = " << cur_assign[i][assign_idx].size() << endl;
            int min_idx = -1;
            int min_value = 1000000000;
            for(int j=0;j<width.size();j++){
                if(width[j] == 0) continue;
                if(cur_height[j] + (a[i][idx] + width[j] - 1) / width[j] < min_value){
                    min_value = cur_height[j] + (a[i][idx] + width[j] - 1) / width[j];
                    min_idx = j;
                }
            }
            // cerr << "min_idx = " << min_idx << endl;
            // cerr << "idx = " << idx << endl;
            // cerr << "new_assign.size() = " << new_assign.size() << endl;
            // cerr << i << endl;
            // cerr << "new_assign[i].size() = " << new_assign[i].size() << endl;
            // cerr << new_assign[i][min_idx].size() << endl;
            new_assign[i][min_idx].push_back(idx);
            // cerr << "cur_height.size() = " << cur_height.size() << endl;
            // cerr << cur_height[min_idx] << endl;
            // cerr << a[i][idx] << endl;
            // cerr << width[min_idx] << endl;
            cur_height[min_idx] += (a[i][idx] + width[min_idx] - 1) / width[min_idx];
            if(used[assign_idx] < cur_assign[i][assign_idx].size()){
                int target_idx = cur_assign[i][assign_idx][used[assign_idx]];
                qu.emplace(a[i][target_idx], target_idx);
                cur_height[assign_idx] -= (a[i][target_idx] + width[assign_idx] - 1) / width[assign_idx];
                used[assign_idx] += 1;
            }

            // cerr << "pushed" << endl;
        }
        // cerr << "end " << endl;
        for(int j=0;j<width.size();j++){
            new_cost += 100 * max(0, cur_height[j] - W);
            if(i != 0){
                new_cost += width[j] * (max(1, (int)new_assign[i][j].size()) - 1);
            }
        }
    }
    // cerr << "New Assign" << endl;
    bool ok = true;
    for(int i=0;i<new_assign.size();i++){
        int num = 0;
        for(int j=0;j<new_assign[i].size();j++){
            // cerr << "Day " << i << " Width " << width[j] << " : ";
            num += new_assign[i][j].size();
            for(int k=0;k<new_assign[i][j].size();k++){
                if(k != 0 && new_assign[i][j][k] > new_assign[i][j][k-1]){
                    ok = false;
                }
                // cerr << new_assign[i][j][k] << " ";
            }
            // cerr << endl;
        }
        if(num != a[i].size()){
            ok = false;
        }
    }
    if(!ok){
        cerr << "Error" << endl;
        exit(1);
    }
    // cerr << "cost = " << new_cost << endl;
    return make_pair(new_cost, new_assign);

}

//------------------------------------------------------------------------------
pair<vector<int>, vector<vector<vector<int>>>> gen_partition(int W, const vector<vector<int>>& a, const Timer& timer){
    vector<int> width(1, W);
    width.reserve(W);
    long long current_cost = 0;
    vector<vector<vector<int>>> assign(a.size(), vector<vector<int>>(1, vector<int>(a[0].size(), 0)));
    for(int i=0;i<a.size();i++){
        int sum = 0;
        for(int j=0;j<a[i].size();j++){
            assign[i][0][j] = a[i].size()-1-j;
            sum += (a[i][a[i].size()-1-j] + W - 1) / W;
        }
        if(i != 0) current_cost += W * (a[i].size() - 1);
        current_cost += 100 * max(0, sum - W);
    }
    for(int i=0;i<a.size();i++){
        cerr << "Day " << i << endl;
        for(int j=0;j<assign[i][0].size();j++){
            cerr << assign[i][0][j] << " ";
        }
        cerr << endl;
    }
    XorShift rnd(1234567891);
    while(timer.msec() < 1500){
        int type = rnd() % 16;
        // cerr << type << " " << timer.msec() << endl;
        if(type == 0){
            if(width.size() == W) continue;
            int idx = rnd() % width.size();
            while(width[idx] <= 1){
                idx = rnd() % width.size();
            }
            int new_width = rnd() % (width[idx] - 1) + 1;
            width.push_back(width[idx] - new_width);
            width[idx] = new_width;
            auto [new_cost, new_assign] = calc_partition_cost(W, a, width, assign);
            if(new_cost < current_cost){
                current_cost = new_cost;
                assign = new_assign;
            } else {
                width[idx] += width.back();
                width.pop_back();
            }
        } else if(type == 1){
            if(width.size() == 1) continue;
            int idx0 = rnd() % width.size();
            int idx1 = rnd() % width.size();
            while(idx0 == idx1){
                idx1 = rnd() % width.size();
            }
            int cur_width = width[idx0];
            width[idx0] += width[idx1];
            width[idx1] = 0;
            auto [new_cost, new_assign] = calc_partition_cost(W, a, width, assign);
            if(new_cost < current_cost){
                current_cost = new_cost;
                assign = new_assign;
                for(auto& asg : assign){
                    swap(asg[idx1], asg.back());
                    asg.pop_back();
                }
                width[idx1] = width.back();
                width.pop_back();
            } else {
                width[idx1] = width[idx0] - cur_width;
                width[idx0] = cur_width;
            }
        } else {
            if(width.size() == 1) continue;
            int idx0 = rnd() % width.size();
            while(width[idx0] == 1){
                idx0 = rnd() % width.size();
            }
            int idx1 = rnd() % width.size();
            while(idx0 == idx1){
                idx1 = rnd() % width.size();
            }
            int chg = rnd() % (width[idx0] - 1) + 1;
            width[idx0] -= chg;
            width[idx1] += chg;
            auto [new_cost, new_assign] = calc_partition_cost(W, a, width, assign);
            if(new_cost < current_cost){
                current_cost = new_cost;
                assign = new_assign;
            } else {
                width[idx1] -= chg;
                width[idx0] += chg;
            }
        }
    }
    return make_pair(width, assign);
}

//------------------------------------------------------------------------------
int main(){
    Timer timer;
    int W, D, N;
    cin >> W >> D >> N;
    vector<vector<int>> a(D, vector<int>(N));
    for(auto& v : a){
        for(auto& t : v){
            cin >> t;
        }
    }
    const double time_limit = 2950;
    XorShift rnd(1234567891);
    auto r = merge_days(a, W);
    cerr << r.first.size() << endl;
    auto [width, assign] = gen_partition(W, r.first, timer);
    for (auto& w : width) {
        cerr << w << " ";
    }
    cerr << endl;
    for(int i=0;i<r.first.size();i++){
        vector<vector<int>> heights(width.size());
        for(auto& asg : assign[i]) cerr << asg.size() << " ";
        cerr << endl;
        for(int j=0;j<width.size();j++){
            int sum = 0;
            for(int k=0;k<assign[i][j].size();k++){
                heights[j].push_back((r.first[i][assign[i][j][k]] + width[j] - 1) / width[j]);
                sum += heights[j].back();
            }
            if(heights[j].empty()) continue;
            while(sum > W){
                int idx = rnd() % heights[j].size();
                if(heights[j][idx] > 1){
                    heights[j][idx] -= 1;
                    sum -= 1;
                }
            }
            if(sum < W) heights[j].back() += W - sum;
        }
        vector<pair<int, tuple<int, int, int, int>>> res;
        int prev_w = 0;
        for(int k=0;k<width.size();k++){
            int new_W = prev_w + width[k];
            int prev_h = 0;
            for(int l=0;l<heights[k].size();l++){
                int new_h = prev_h + heights[k][l];
                res.emplace_back((new_h-prev_h)*(new_W-prev_w), make_tuple(prev_w, prev_h, new_W, new_h));
                // cout << prev_w << " " << prev_h << " " << new_W << " " << new_h << endl;
                prev_h = new_h;
            }
            prev_w = new_W;
        }
        sort(res.begin(), res.end());
        for(int j=0;j<r.second[i];j++){
            for(int k=0;k<res.size();k++){
                auto [x1, y1, x2, y2] = res[k].second;
                cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
            }
        }
    }
}