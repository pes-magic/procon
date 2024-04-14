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

const int MOD = 998244353;
const int dd[] = {0, 1, 2, 9, 10, 11, 18, 19, 20};

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
class Action {
public:
    Action(int m, int p, int q) : m(m), p(p), q(q) {}
    ostream& print(ostream& os) const {
        os << m << " " << p << " " << q;
        return os;
    }
    int m, p, q;
};

ostream& operator << (ostream& os, const Action& a){
    return a.print(os);
}

//------------------------------------------------------------------------------
void make_stump(
    vector<vector<pair<vector<int>, vector<int>>>>& merged_stump,
    vector<int>& cur_set,
    vector<int>& cur_stump,
    int idx,
    const vector<vector<int>>& stump)
{
    if(cur_set.size() == 8) return;
    for(int i=idx;i<stump.size();i++){
        for(int j=0;j<9;j++){
            cur_stump[j] += stump[i][j];
            cur_stump[j] %= MOD;
        }
        cur_set.push_back(i);
        merged_stump[cur_set.size() - 1].emplace_back(cur_set, cur_stump);
        make_stump(merged_stump, cur_set, cur_stump, i, stump);
        cur_set.pop_back();
        for(int j=0;j<9;j++){
            cur_stump[j] += MOD - stump[i][j];
            cur_stump[j] %= MOD;
        }
    }
}

//------------------------------------------------------------------------------
int main(){
    Timer timer;
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> a(N * N);
    vector<vector<int>> stump(M, vector<int>(9));
    for(auto& v : a) cin >> v;
    for(auto& s : stump) for(auto& v : s) cin >> v;
    vector<int> cur_set;
    vector<int> cur_stump(9, 0);
    vector<vector<pair<vector<int>, vector<int>>>> merged_stump(9);
    make_stump(merged_stump, cur_set, cur_stump, 0, stump);
    vector<vector<long long>> cost(50, vector<long long>(N*N+1, 0));
    vector<vector<int>> action(50, vector<int>(N*N+1, 0));
    vector<vector<vector<int>>> board(50, vector<vector<int>>(N*N+1, vector<int>(N*N)));
    for(int i=0;i<=81;i++){
        board[0][i] = a;
        if(i != 0) cost[0][i] = -(1LL << 50);
    }
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            int pos = 9*i+j;
            int base = 7*i+j;
            int max_inc = 2;
            if(i==6 && j==6) max_inc = 8;
            if(i==6 || j==6) max_inc = 4;
            for(int k=0;k<=N*N;k++){
                board[base+1][k] = board[base][k];
                cost[base+1][k] = cost[base][k];
                action[base+1][k] = -1;
            }
            for(int k=0;k<=N*N;k++){
                if(cost[base][k] < 0) continue;
                auto cur_board = board[base][k];
                for(int inc=0;inc<max_inc;inc++){
                    if(k+inc+1 > N*N) break;
                    int idx = 0;
                    for(auto& state : merged_stump[inc]){
                        auto& stump = state.second;
                        long long score = 0;
                        for(int l=0;l<9;l++){
                            cur_board[pos+dd[l]] += stump[l];
                            cur_board[pos+dd[l]] %= MOD;
                        }
                        if(i == 6 && j == 6){
                            for(int l=0;l<9;l++){
                                score += cur_board[pos+dd[l]];
                            }
                        } else if(i == 6){
                            for(int l=0;l<9;l+=3){
                                score += cur_board[pos+dd[l]];
                            }
                        } else if(j == 6){
                            for(int l=0;l<3;l++){
                                score += cur_board[pos+dd[l]];
                            }
                        } else {
                            score += cur_board[pos+dd[0]];
                        }
                        if(cost[base][k] + score > cost[base+1][k+inc+1]){
                            cost[base+1][k+inc+1] = cost[base][k] + score;
                            action[base+1][k+inc+1] = 16 * idx + inc;
                            board[base+1][k+inc+1] = cur_board;
                        }
                        for(int l=0;l<9;l++){
                            cur_board[pos+dd[l]] += MOD - stump[l];
                            cur_board[pos+dd[l]] %= MOD;
                        }
                        ++idx;
                    }
                }
            }
        }
    }
    long long best_score = 0;
    int best_stump_num = 0;
    for(int i=0;i<=N*N;i++){
        cerr << i << " " << cost[49][i] << endl;
        if(cost[49][i] > best_score){
            best_score = cost[49][i];
            best_stump_num = i;
        }
    }
    cerr << best_score << endl;
    cout << best_stump_num << endl;
    int cur_idx = 49;
    while(cur_idx > 0){
        if(action[cur_idx][best_stump_num] == -1){
            --cur_idx;
            continue;
        }
        int stump_idx = action[cur_idx][best_stump_num] / 16;
        int inc = action[cur_idx][best_stump_num] % 16;
        for(auto& v : merged_stump[inc][stump_idx].first){
            cout << v << " " << (cur_idx-1)/7 << " " << (cur_idx-1)%7 << endl;
        }
        best_stump_num -= inc + 1;
        --cur_idx;
    }
}