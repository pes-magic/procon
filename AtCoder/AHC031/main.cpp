#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <cassert>
#include <tuple>

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
long long calc_cost_one_day(const int W, const vector<int>& a, const vector<int>& v_line, const vector<int>& h_line, long long order){
    vector<int> area;
    int v_idx = 0, h_idx = 0;
    int v_prev = 0, h_prev = 0;
    for(int i=0;i<v_line.size()+h_line.size();i++){
        if(order&(1LL<<i)){
            area.push_back((h_line[h_idx] - h_prev) * (W - v_prev));
            h_prev = h_line[h_idx];
            h_idx++;
        } else {
            area.push_back((v_line[v_idx] - v_prev) * (W - h_prev));
            v_prev = v_line[v_idx];
            v_idx++;
        }
    }
    area.push_back((W - v_prev) * (W - h_prev));
    sort(area.begin(), area.end());
    long long cost = 0;
    for(int i=0;i<a.size();i++){
        cost += 100 * max(0, a[i] - area[i]);
    }
    return cost;
}

//------------------------------------------------------------------------------
long long calc_cost(const int W, const vector<vector<int>>& a, const vector<int>& v_line, const vector<int>& h_line, long long order){
    vector<int> area;
    int v_idx = 0, h_idx = 0;
    int v_prev = 0, h_prev = 0;
    for(int i=0;i<v_line.size()+h_line.size();i++){
        if(order&(1LL<<i)){
            area.push_back((h_line[h_idx] - h_prev) * (W - v_prev));
            h_prev = h_line[h_idx];
            h_idx++;
        } else {
            area.push_back((v_line[v_idx] - v_prev) * (W - h_prev));
            v_prev = v_line[v_idx];
            v_idx++;
        }
    }
    area.push_back((W - v_prev) * (W - h_prev));
    sort(area.begin(), area.end());
    long long cost = 0;
    for(auto& v : a){
        for(int i=0;i<v.size();i++){
            cost += 100 * max(0, v[i] - area[i]);
        }
    }
    return cost;
}

//------------------------------------------------------------------------------
void print_rectangle(const int W, const vector<int>& v_line, const vector<int>& h_line, long long order){
    int v_idx = 0, h_idx = 0;
    int v_prev = 0, h_prev = 0;
    vector<pair<int, tuple<int, int, int, int>>> rect;
    for(int i=0;i<v_line.size()+h_line.size();i++){
        if(order&(1LL<<i)){
            int area = (h_line[h_idx] - h_prev) * (W - v_prev);
            rect.emplace_back(area, make_tuple(v_prev, h_prev, W, h_line[h_idx]));
            h_prev = h_line[h_idx];
            h_idx++;
        } else {
            int area = (v_line[v_idx] - v_prev) * (W - h_prev);
            rect.emplace_back(area, make_tuple(v_prev, h_prev, v_line[v_idx], W));
            v_prev = v_line[v_idx];
            v_idx++;
        }
    }
    rect.emplace_back((W - v_prev) * (W - h_prev), make_tuple(v_prev, h_prev, W, W));
    sort(rect.begin(), rect.end());
    for(auto& [area, r] : rect){
        auto [v_prev, h_prev, v, h] = r;
        cout << v_prev << " " << h_prev << " " << v << " " << h << endl;
    }
}

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
int main(){
    Timer timer;
    const double initial_temp = 5000.0;
    const double final_temp = 0.0;
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
    vector<int> v_line;
    vector<int> h_line;
    vector<int> v_use(W+1, 0);
    vector<int> h_use(W+1, 0);
    long long order = 0LL;
    {
        v_use[0] = 1;
        h_use[0] = 1;
        v_use[W] = 1;
        h_use[W] = 1;
        for(int i=0;i<N-1;i++){
            if(i % 2){
                v_line.push_back(rnd() % (W-1) + 1);
                while(v_use[v_line.back()]){
                    v_line.back() = rnd() % (W-1) + 1;
                }
                v_use[v_line.back()] = 1;
            }else{
                h_line.push_back(rnd() % (W-1) + 1);
                while(h_use[h_line.back()]){
                    h_line.back() = rnd() % (W-1) + 1;
                }
                h_use[h_line.back()] = 1;
            }
        }
        sort(v_line.begin(), v_line.end());
        sort(h_line.begin(), h_line.end());
        for(int i=0;i<h_line.size();i++){
            while(true) {
                int t = rnd() % (N-2) + 1;
                if(order&(1LL << t)) continue;
                order |= 1LL << t;
                break;
            }
        }
    }
    auto r = merge_days(a, W);
    for(int day=0;day<r.first.size();day++){
        long long cur_score = calc_cost_one_day(W, r.first[day], v_line, h_line, order);
        long long best_score = cur_score;
        vector<int> best_v_line = v_line;
        vector<int> best_h_line = h_line;
        long long best_order = order;
        cerr << "Initial score: " << cur_score << endl;
        const double time_start = timer.msec();
        const double time_end = time_limit / r.first.size() * (day + 1);
        while(best_score > 0 && timer.msec() < time_end){
            int chg_v_idx = -1;
            int chg_h_idx = -1;
            int chg_v_value = -1;
            int chg_h_value = -1;
            int chg_order_idx = -1;
            if(rnd() % 4){
                if(rnd()% 2){
                    while(true){
                        int sgn = rnd() % 2 ? 1 : -1;
                        int idx = rnd() % v_line.size();
                        if(!v_use[v_line[idx] + sgn]){
                            chg_v_idx = idx;
                            chg_v_value = sgn;
                            v_line[idx] += sgn;
                            break;
                        }
                    }
                } else {
                    while(true){
                        int sgn = rnd() % 2 ? 1 : -1;
                        int idx = rnd() % h_line.size();
                        if(!h_use[h_line[idx] + sgn]){
                            chg_h_idx = idx;
                            chg_h_value = sgn;
                            h_line[idx] += sgn;
                            break;
                        }
                    }
                }
            } else {
                while(true){
                    int idx = rnd() % (N-3) + 1;
                    if((order >> idx)%4%3 != 0){
                        chg_order_idx = idx;
                        order ^= 3LL << idx;
                        break;
                    }
                }
            }
            long long new_score = calc_cost_one_day(W, r.first[day], v_line, h_line, order);
            const double ratio = (timer.msec() - time_start) / (time_end - time_start);
            const double rev_ratio = 1 - ratio;
            const double temperature = initial_temp + (final_temp - initial_temp) * (1 - rev_ratio * rev_ratio * rev_ratio);
            double delta = new_score - cur_score;
            // スコアがtemperature悪化するときの採用確率は約36.8%
            if(delta < 0 || bernoulli_distribution(exp(-delta/temperature))(rnd)){
                if(chg_v_idx != -1){
                    v_use[v_line[chg_v_idx] - chg_v_value] = 0;
                    v_use[v_line[chg_v_idx]] = 1;
                }
                if(chg_h_idx != -1){
                    h_use[h_line[chg_h_idx] - chg_h_value] = 0;
                    h_use[h_line[chg_h_idx]] = 1;
                }
                cur_score = new_score;
                if(best_score > cur_score){
                    best_score = cur_score;
                    best_v_line = v_line;
                    best_h_line = h_line;
                    best_order = order;
                }
            } else {
                if(chg_v_idx != -1){
                    v_line[chg_v_idx] -= chg_v_value;
                }
                if(chg_h_idx != -1){
                    h_line[chg_h_idx] -= chg_h_value;
                }
                if(chg_order_idx != -1){
                    order ^= 3LL << chg_order_idx;
                }
            }
        }
        int sum = 0;
        for(auto& t : r.first[day]){
            sum += t;
        }
        cerr << sum << "/" << W*W << endl;
        cerr << "Best score: " << best_score << endl;
        for(int _=0;_<r.second[day];_++){
            print_rectangle(W, best_v_line, best_h_line, best_order);
        }
        v_line = best_v_line;
        h_line = best_h_line;
        order = best_order;
        for(int i=1;i<W;i++){
            v_use[i] = 0;
            h_use[i] = 0;
        }
        for(auto& t : v_line){
            v_use[t] = 1;
        }
        for(auto& t : h_line){
            h_use[t] = 1;
        }
    }
    cerr << "Merged size: " << r.first.size() << " " << D << endl;
}