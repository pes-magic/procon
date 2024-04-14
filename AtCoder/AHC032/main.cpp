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
int main(){
    Timer timer;
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> a(N, vector<int>(N));
    auto initial_a = a;
    vector<vector<vector<int>>> stump(M, vector<vector<int>>(3, vector<int>(3)));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < 3; ++j){
            for(int k = 0; k < 3; ++k){
                cin >> stump[i][j][k];
            }
        }
    }
    vector<Action> actions;
    for(int _=0;_<K;_++){
        long long best_score = 0;
        Action best_action = Action(0, 0, 0);
        for(int p=0;p<N-2;p++){
            for(int q=0;q<N-2;q++){
                long long base_score = 0;
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        base_score -= a[p+i][q+j];
                    }
                }
                for(int m=0;m<M;m++){
                    long long score = base_score;
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                            a[p+i][q+j] += stump[m][i][j];
                            a[p+i][q+j] %= MOD;
                            score += a[p+i][q+j];
                            a[p+i][q+j] += MOD - stump[m][i][j];
                            a[p+i][q+j] %= MOD;
                        }
                    }
                    if(score > best_score){
                        best_score = score;
                        best_action = Action(m, p, q);
                    }
                }
            }
        }
        if(best_score > 0){
            actions.push_back(best_action);
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    a[best_action.p+i][best_action.q+j] += stump[best_action.m][i][j];
                    a[best_action.p+i][best_action.q+j] %= MOD;
                }
            }
        }
    }
    long long first_sum = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            first_sum += a[i][j];
        }
    }
    XorShift rnd(1234567891);
    const double start_time = timer.msec();
    const double end_time = 1950.0;
    double cur_time = start_time;
    const double initial_temp = 1000000000;
    const double final_temp = 0.001;
    long long best_score = 0;
    vector<Action> best_actions = actions;
    Action tmp_action = Action(0, 0, 0);
    Action tmp_action2 = Action(0, 0, 0);
    long long cur_score = 0;

    while(timer.msec() < end_time){
        int p = rnd() % 16;
        long long dif_score = 0;
        int chg_idx = -1;
        int chg_idx2 = -1;
        if(p == 0 && actions.size() < K){
            actions.emplace_back(rnd() % M, rnd() % (N - 2), rnd() % (N - 2));
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    dif_score -= a[actions.back().p+i][actions.back().q+j];
                    a[actions.back().p+i][actions.back().q+j] += stump[actions.back().m][i][j];
                    a[actions.back().p+i][actions.back().q+j] %= MOD;
                    dif_score += a[actions.back().p+i][actions.back().q+j];
                }
            }
        } else if(p == 1 && actions.size() >= 2){
            int idx = rnd() % actions.size();
            if(idx != actions.size() - 1) swap(actions[idx], actions.back());
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    dif_score -= a[actions.back().p+i][actions.back().q+j];
                    a[actions.back().p+i][actions.back().q+j] += MOD - stump[actions.back().m][i][j];
                    a[actions.back().p+i][actions.back().q+j] %= MOD;
                    dif_score += a[actions.back().p+i][actions.back().q+j];
                }
            }
        } else {
            chg_idx = rnd() % actions.size();
            if(actions.size() >= 10 && rnd() % 4 == 0){
                chg_idx2 = rnd() % actions.size();
                while(chg_idx2 == chg_idx) chg_idx2 = rnd() % actions.size();
            }
            tmp_action = actions[chg_idx];
            if(chg_idx2 != -1) tmp_action2 = actions[chg_idx2];
            actions[chg_idx] = Action(rnd() % M, rnd() % (N - 2), rnd() % (N - 2));
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    dif_score -= a[tmp_action.p+i][tmp_action.q+j];
                    a[tmp_action.p+i][tmp_action.q+j] += MOD - stump[tmp_action.m][i][j];
                    a[tmp_action.p+i][tmp_action.q+j] %= MOD;
                    dif_score += a[tmp_action.p+i][tmp_action.q+j];
                    dif_score -= a[actions[chg_idx].p+i][actions[chg_idx].q+j];
                    a[actions[chg_idx].p+i][actions[chg_idx].q+j] += stump[actions[chg_idx].m][i][j];
                    a[actions[chg_idx].p+i][actions[chg_idx].q+j] %= MOD;
                    dif_score += a[actions[chg_idx].p+i][actions[chg_idx].q+j];
                    if(chg_idx2 != -1){
                        dif_score -= a[tmp_action2.p+i][tmp_action2.q+j];
                        a[tmp_action2.p+i][tmp_action2.q+j] += MOD - stump[tmp_action2.m][i][j];
                        a[tmp_action2.p+i][tmp_action2.q+j] %= MOD;
                        dif_score += a[tmp_action2.p+i][tmp_action2.q+j];
                        dif_score -= a[actions[chg_idx2].p+i][actions[chg_idx2].q+j];
                        a[actions[chg_idx2].p+i][actions[chg_idx2].q+j] += stump[actions[chg_idx2].m][i][j];
                        a[actions[chg_idx2].p+i][actions[chg_idx2].q+j] %= MOD;
                        dif_score += a[actions[chg_idx2].p+i][actions[chg_idx2].q+j];
                    }
                }
            }
        }
        const double ratio = (timer.msec() - start_time) / (end_time - start_time);
        const double temperature = initial_temp + (final_temp - initial_temp) * ratio;
        double delta = dif_score;
        if(delta > 0 || bernoulli_distribution(exp(delta/temperature))(rnd)){
            cur_score += delta;
            if(p == 1 && chg_idx == -1){
                actions.pop_back();
            }
            if(cur_score > best_score){
                best_score = cur_score;
                best_actions = actions;
            }
        } else {
            if(chg_idx != -1){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        a[actions[chg_idx].p+i][actions[chg_idx].q+j] += MOD - stump[actions[chg_idx].m][i][j];
                        a[actions[chg_idx].p+i][actions[chg_idx].q+j] %= MOD;
                    }
                }
                actions[chg_idx] = tmp_action;
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        a[actions[chg_idx].p+i][actions[chg_idx].q+j] += stump[actions[chg_idx].m][i][j];
                        a[actions[chg_idx].p+i][actions[chg_idx].q+j] %= MOD;
                    }
                }
                if(chg_idx2 != -1){
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                            a[actions[chg_idx2].p+i][actions[chg_idx2].q+j] += MOD - stump[actions[chg_idx2].m][i][j];
                            a[actions[chg_idx2].p+i][actions[chg_idx2].q+j] %= MOD;
                        }
                    }
                    actions[chg_idx2] = tmp_action2;
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                            a[actions[chg_idx2].p+i][actions[chg_idx2].q+j] += stump[actions[chg_idx2].m][i][j];
                            a[actions[chg_idx2].p+i][actions[chg_idx2].q+j] %= MOD;
                        }
                    }
                }
            } else if (p == 0){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        a[actions.back().p+i][actions.back().q+j] += MOD - stump[actions.back().m][i][j];
                        a[actions.back().p+i][actions.back().q+j] %= MOD;
                    }
                }
                actions.pop_back();
            } else {
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        a[actions.back().p+i][actions.back().q+j] += stump[actions.back().m][i][j];
                        a[actions.back().p+i][actions.back().q+j] %= MOD;
                    }
                }
            }
        }

        cur_time = timer.msec();
    }
    cerr << "score: " << best_score << endl;


    // a = initial_a;
    // for(auto& act : best_actions){
    //     for(int i=0;i<3;i++){
    //         for(int j=0;j<3;j++){
    //             a[act.p+i][act.q+j] += stump[act.m][i][j];
    //             a[act.p+i][act.q+j] %= MOD;
    //         }
    //     }
    // }
    long long sum = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            sum += a[i][j];
        }
    }
/*
    for(int _=best_actions.size();_<K;_++){
        long long best_score = 0;
        Action best_action = Action(0, 0, 0);
        for(int p=0;p<N-2;p++){
            for(int q=0;q<N-2;q++){
                long long base_score = 0;
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        base_score -= a[p+i][q+j];
                    }
                }
                for(int m=0;m<M;m++){
                    long long score = base_score;
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                            a[p+i][q+j] += stump[m][i][j];
                            a[p+i][q+j] %= MOD;
                            score += a[p+i][q+j];
                            a[p+i][q+j] += MOD - stump[m][i][j];
                            a[p+i][q+j] %= MOD;
                        }
                    }
                    if(score > best_score){
                        best_score = score;
                        best_action = Action(m, p, q);
                    }
                }
            }
        }
        if(best_score > 0){
            best_actions.push_back(best_action);
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    a[best_action.p+i][best_action.q+j] += stump[best_action.m][i][j];
                    a[best_action.p+i][best_action.q+j] %= MOD;
                }
            }
        }
    }
*/
    cerr << "score = " << sum << ", " << first_sum + cur_score << endl;;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cerr << a[i][j] << " ";
        }
        cerr << endl;
    }
    for(int _=best_actions.size();_<K;_++){
        long long best_score = 0;
        Action best_action = Action(0, 0, 0);
        for(int p=0;p<N-2;p++){
            for(int q=0;q<N-2;q++){
                long long base_score = 0;
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        base_score -= a[p+i][q+j];
                    }
                }
                for(int m=0;m<M;m++){
                    long long score = base_score;
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                            a[p+i][q+j] += stump[m][i][j];
                            a[p+i][q+j] %= MOD;
                            score += a[p+i][q+j];
                            a[p+i][q+j] += MOD - stump[m][i][j];
                            a[p+i][q+j] %= MOD;
                        }
                    }
                    if(score > best_score){
                        best_score = score;
                        best_action = Action(m, p, q);
                    }
                }
            }
        }
        if(best_score > 0){
            best_actions.push_back(best_action);
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    a[best_action.p+i][best_action.q+j] += stump[best_action.m][i][j];
                    a[best_action.p+i][best_action.q+j] %= MOD;
                }
            }
        }
    }
    cerr << best_score << endl;
    cout << best_actions.size() << endl;
    for(auto& a : best_actions) cout << a << endl;
}
