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
    std::ios::sync_with_stdio(false);
    int N, M; cin >> N >> M;
    vector<vector<int>> board(N+2, vector<int>(N+2, 0));
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin >> board[i][j];
        }
    }

    const double initial_temp = 1.0;
    const double final_temp = 1e-3;
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};
    vector<vector<bool>> is_adj(M+1, vector<bool>(M+1, false));
    vector<vector<int>> adj_cnt(M+1, vector<int>(M+1, 0));
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            for(int k=0;k<2;k++){
                int ni = i + dx[k];
                int nj = j + dy[k];
                if(board[i][j] != board[ni][nj]){
                    is_adj[board[i][j]][board[ni][nj]] = true;
                    adj_cnt[board[i][j]][board[ni][nj]]++;
                }
            }
        }
    }
    for(int i=0;i<=M;i++){
        for(int j=i+1;j<=M;j++){
            if(is_adj[i][j] || is_adj[j][i]){
                is_adj[i][j] = is_adj[j][i] = true;
            }
        }
    }
    const double start_time = timer.msec();
    double cur_time = start_time;
    int best_score = 0;
    int cur_score = 0;
    XorShift rnd(chrono::steady_clock::now().time_since_epoch().count());
    int src_x = 1;
    int dst_x = N;
    int src_y = 1;
    int dst_y = N;

    auto check_naive = [&]() -> bool {
        vector<vector<int>> cnt(M+1, vector<int>(M+1, 0));
        vector<int> color_cnt(M+1, 0);
        UnionFind uf((N+2)*(N+2));
        int groups = (N+2)*(N+2);
        for(int i=0;i<=N;i++){
            for(int j=0;j<=N;j++){
                for(int k=0;k<2;k++){
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    color_cnt[board[i][j]]++;
                    if(board[i][j] != board[ni][nj]){
                        cnt[board[i][j]][board[ni][nj]]++;
                    } else {
                        if(uf.merge(i*(N+2)+j, ni*(N+2)+nj)) --groups;
                    }
                }
            }
            if(uf.merge((N+1)*(N+2)+i, (N+1)*(N+2)+i+1)) --groups;
            if(uf.merge(i*(N+2)+N+1, (i+1)*(N+2)+N+1)) --groups;
        }
        if(groups != M+1) return false;
        for(int i=0;i<=M;i++){
            if(color_cnt[i] == 0) return false;
            for(int j=i+1;j<=M;j++){
                if((cnt[i][j] + cnt[j][i] != 0) ^ is_adj[i][j]){
                    return false;
                }
            }
        }
        return true;
    };

    while(true){
        bool end0 = true;
        auto cur = board;
        vector<int> keep(N+2, 0);
        for(int i=dst_x;i>=1;i--){
            for(int j=1;j<=dst_y;j++){
                int t = board[i][j];
                board[i][j] = keep[j];
                keep[j] = t;
            }
            if(check_naive()){
                for(int i=1;i<=N;i++){
                    for(int j=1;j<=N;j++){
                        cout << board[i][j] << " ";
                    }
                    cout << endl;
                }
                end0 = false;
                cur = board;
                --dst_x;
                cur_score += dst_y;
                break;
            }
        }
        if(end0) board = cur;
        bool end1 = true;
        std::fill(keep.begin(), keep.end(), 0);
        for(int j=dst_y;j>=1;j--){
            for(int i=1;i<=dst_x;i++){
                int t = board[i][j];
                board[i][j] = keep[i];
                keep[i] = t;
            }
            if(check_naive()){
                end1 = false;
                for(int i=1;i<=N;i++){
                    for(int j=1;j<=N;j++){
                        cout << board[i][j] << " ";
                    }
                    cout << endl;
                }
                cur_score += dst_x;
                --dst_y;
                break;
            }
        }
        if(end1) board = cur;
        if(end0 && end1) break;
    }

    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    for(int i=0;i<=M;i++) std::fill(adj_cnt[i].begin(), adj_cnt[i].end(), 0);
    for(int i=0;i<=dst_x;i++){
        for(int j=0;j<=dst_y;j++){
            for(int k=0;k<2;k++){
                int ni = i + dx[k];
                int nj = j + dy[k];
                if(board[i][j] != board[ni][nj]){
                    adj_cnt[board[i][j]][board[ni][nj]]++;
                }
            }
        }
    }

    auto change_board = [&](int x, int y, int new_color) -> int {
        const auto cur_adj_cnt  = adj_cnt;
        for(int k=0;k<4;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(board[x][y] != board[nx][ny]){
                --adj_cnt[board[x][y]][board[nx][ny]];
            }
        }
        int cur = board[x][y];
        if(cur == 0) --cur_score;
        board[x][y] = new_color;
        if(new_color == 0) ++cur_score;
        for(int k=0;k<4;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(board[x][y] != board[nx][ny]){
                ++adj_cnt[board[x][y]][board[nx][ny]];
            }
        }

        return cur;
    };


    vector<vector<int>> visit(N+2, vector<int>(N+2, 0));

    auto check_valid = [&](int x, int y, int prev_color) -> bool {
                // return check_naive();

        int check_color[] = {board[x][y], prev_color};
        for(auto& color: check_color){
            for(int k=0;k<4;k++){
                const int nx = x + dx[k];
                const int ny = y + dy[k];
                const int new_color = board[nx][ny];
                if(color == new_color){
                    continue;
                }
                if((adj_cnt[color][new_color] + adj_cnt[new_color][color] != 0)^is_adj[color][new_color]){
                    return false;
                }
            }
        }
        const int x0 = board[x-1][y-1] == prev_color ? 1 : 0;
        const int x1 = board[x-1][y] == prev_color ? 1 : 0;
        const int x2 = board[x-1][y+1] == prev_color ? 1 : 0;
        const int x3 = board[x][y-1] == prev_color ? 1 : 0;
        const int x5 = board[x][y+1] == prev_color ? 1 : 0;
        const int x6 = board[x+1][y-1] == prev_color ? 1 : 0;
        const int x7 = board[x+1][y] == prev_color ? 1 : 0;
        const int x8 = board[x+1][y+1] == prev_color ? 1 : 0;
        if(x1 + x3 + x5 + x7 - x0*x1*x3 - x2*x1*x5 - x6*x3*x7 - x8*x5*x7 != 1) return false;
        int src_x = max(0, x-3);
        int dst_x = min(N+1, x+3);
        int src_y = max(0, y-3);
        int dst_y = min(N+1, y+3);
        int cnt = 0;
        int sx = 0, sy = 0;
        for(int i=src_x;i<=dst_x;i++){
            for(int j=src_y;j<=dst_y;j++){
                if(board[i][j] == 0){
                    cnt++;
                }
                visit[i][j] = 0;
            }
        }
        if(cnt <= 1) return true;
        queue<pair<int, int>> qu;
        qu.emplace(x, y);
        visit[x][y] = 1;
        --cnt;
        while(!qu.empty()){
            auto [cx, cy] = qu.front(); qu.pop();
            for(int k=0;k<4;k++){
                const int nx = cx + dx[k];
                const int ny = cy + dy[k];
                if(nx < 0 || N+1 < nx || ny < 0 || N+1 < ny) continue;
                if(visit[nx][ny] == 0 && board[nx][ny] == 0){
                    visit[nx][ny] = 1;
                    qu.emplace(nx, ny);
                    --cnt;
                }
            }
        }
        return cnt == 0;
    };

    vector<vector<int>> original_board(N, vector<int>(N));

    const double time_limit = 1950.0;
    auto best_board = board;
    int shown_score = cur_score;
    int rep_cnt = 0;
    while(cur_time < time_limit){
        ++rep_cnt;
        if(rep_cnt % 1024 == 0){
            bool end0 = true;
            auto cur = board;
            vector<int> keep(N+2, 0);
            for(int i=dst_x;i>=1;i--){
                for(int j=1;j<=dst_y;j++){
                    int t = board[i][j];
                    board[i][j] = keep[j];
                    keep[j] = t;
                }
                if(check_naive()){
                    for(int i=1;i<=N;i++){
                        for(int j=1;j<=N;j++){
                            cout << board[i][j] << " ";
                        }
                        cout << endl;
                    }
                    end0 = false;
                    cur = board;
                    --dst_x;
                    break;
                }
            }
            if(end0) board = cur;
            bool end1 = true;
            std::fill(keep.begin(), keep.end(), 0);
            for(int j=dst_y;j>=1;j--){
                for(int i=1;i<=dst_x;i++){
                    int t = board[i][j];
                    board[i][j] = keep[i];
                    keep[i] = t;
                }
                if(check_naive()){
                    end1 = false;
                    for(int i=1;i<=N;i++){
                        for(int j=1;j<=N;j++){
                            cout << board[i][j] << " ";
                        }
                        cout << endl;
                    }
                    --dst_y;
                    break;
                }
            }
            if(end1) board = cur;
            if(!end0 || !end1){
                for(int i=0;i<=M;i++) std::fill(adj_cnt[i].begin(), adj_cnt[i].end(), 0);
                for(int i=0;i<=dst_x;i++){
                    for(int j=0;j<=dst_y;j++){
                        for(int k=0;k<2;k++){
                            int ni = i + dx[k];
                            int nj = j + dy[k];
                            if(board[i][j] != board[ni][nj]){
                                adj_cnt[board[i][j]][board[ni][nj]]++;
                            }
                        }
                    }
                }
                cur_score = 0;
                for(int i=1;i<=N;i++){
                    for(int j=1;j<=N;j++){
                        if(board[i][j] == 0) ++cur_score;
                    }
                }
                if(cur_score > best_score){
                    best_score = cur_score;
                    shown_score = best_score;
                    best_board = board;
                }
            }
        }
        const int prev_score = cur_score;
        int x = rnd.random_range(src_x, dst_x);
        int y = rnd.random_range(src_y, dst_y);
        int dir = rnd.random_range(0, 3);
        while(true){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if(board[x][y] != board[nx][ny]){
                break;
            }
            x = rnd.random_range(src_x, dst_x);
            y = rnd.random_range(src_y, dst_y);
            dir = rnd.random_range(0, 3);
        }

        const int nx = x + dx[dir];
        const int ny = y + dy[dir];
        int dif = 0;
        vector<int> prev;
        prev.push_back(change_board(x, y, board[nx][ny]));
        bool b0 = check_valid(x, y, prev[0]);
        int last_valid = (b0 ? 0 : -1);
        bool multi = false;
        if(!b0){
            multi = true;
            dif = rnd()%2 * 2 + 1;
            int cx = x + dx[(dir+dif)%4];
            int cy = y + dy[(dir+dif)%4];
            int ncx = nx + dx[(dir+dif)%4];
            int ncy = ny + dy[(dir+dif)%4];
            if(cx <= 0 || N < cx || cy <= 0 || N < cy){
                dif = 4 - dif;
                cx = x + dx[(dir+dif)%4];
                cy = y + dy[(dir+dif)%4];
                ncx = nx + dx[(dir+dif)%4];
                ncy = ny + dy[(dir+dif)%4];
            }
            prev.push_back(change_board(cx, cy, board[ncx][ncy]));
            bool b = check_naive();
            if(b){
                last_valid = 1;
            }
        }

        const double ratio = (cur_time - start_time) / (time_limit - start_time);
        const double temp = initial_temp + (final_temp - initial_temp) * ratio;
        const int score_dif = cur_score - prev_score;
        if(last_valid != -1 && (score_dif >= 0 || bernoulli_distribution(exp(score_dif / temp))(rnd))){
            if(cur_score > best_score){
                best_score = cur_score;
                best_board = board;
                if(shown_score + 20 < best_score){
                    shown_score = best_score;
                    for(int i=1;i<=N;i++){
                        for(int j=1;j<=N;j++){
                            cout << board[i][j] << " ";
                        }
                        cout << endl;
                    }
                }
            }
        } else {
            for(int i=(int)prev.size()-1;i>=0;i--){
                change_board(x + i * dx[(dir+dif)%4], y + i * dy[(dir+dif)%4], prev[i]);
            }
        }

        cur_time = timer.msec();
    }
    cerr << "rep_cnt: " << rep_cnt << endl;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}