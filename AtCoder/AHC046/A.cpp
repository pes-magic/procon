#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>

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

bool debug = false;

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

XorShift rnd(1234567891);

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

vector<vector<vector<int>>> genWapp(int N, const vector<int>& board) {
    vector<vector<vector<int>>> warp(4, vector<vector<int>>(board.size(), vector<int>(board.size(), 0)));
    // down
    for(int i=0;i<N;i++){
        int t = N-1;
        for(int j=N-1;j>=0;j--){
            if(board[j] & (1 << i)){
                t = j-1;
            }
            warp[0][j][i] = t;
        }
    }
    // right
    for(int i=0;i<N;i++){
        int t = N-1;
        for(int j=N-1;j>=0;j--){
            if(board[i] & (1 << j)){
                t = j-1;
            }
            warp[1][i][j] = t;
        }
    }
    // up
    for(int i=0;i<N;i++){
        int t = 0;
        for(int j=0;j<N;j++){
            if(board[j] & (1 << i)){
                t = j+1;
            }
            warp[2][j][i] = t;
        }
    }
    // left
    for(int i=0;i<N;i++){
        int t = 0;
        for(int j=0;j<N;j++){
            if(board[i] & (1 << j)){
                t = j+1;
            }
            warp[3][i][j] = t;
        }
    }

    return warp;
}



int minCost(int x, int y, int step, const vector<pair<int, int>>& target, const vector<int>& board, const vector<vector<vector<int>>>& warp) {
    int N = board.size();
    int cost = 0;
    vector<vector<int>> dist(N, vector<int>(N, 1000000));
    for(int s=step;s<target.size();s++){
        for(auto& v : dist){
            fill(v.begin(), v.end(), 1000000);
        }
        dist[x][y] = 0;
        queue<pair<int, int>> qu;
        qu.emplace(x, y);
        while(!qu.empty()){
            auto [cx, cy] = qu.front();
            if(cx == target[s].first && cy == target[s].second){
                x = cx;
                y = cy;
                cost += dist[cx][cy];
                break;
            }
            qu.pop();
            for(int d=0;d<4;d++){
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if(board[nx] & (1 << ny)) continue;
                if(dist[nx][ny] > dist[cx][cy] + 1){
                    dist[nx][ny] = dist[cx][cy] + 1;
                    qu.emplace(nx, ny);
                }
            }
            for(int d=0;d<4;d++){
                int nx = d%2 == 0 ? warp[d][cx][cy] : cx;
                int ny = d%2 == 1 ? warp[d][cx][cy] : cy;
                if(dist[nx][ny] > dist[cx][cy]){
                    dist[nx][ny] = dist[cx][cy] + 1;
                    qu.emplace(nx, ny);
                }
            }
        }
        if(x != target[s].first || y != target[s].second){
            return 1000000;
        }
    }
    return cost;
}

int minCost(int x, int y, int step, const vector<pair<int, int>>& target, const vector<int>& board) {
    int N = board.size();
    auto warp = genWapp(N, board);
    return minCost(x, y, step, target, board, warp);
}

int main(){
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> target(M);
    for (int i = 0; i < M; i++) {
        cin >> target[i].first >> target[i].second;
    }
    vector<int> board(N, 0);
    int x = target[0].first;
    int y = target[0].second;
    int seek = 1;
    auto warp = genWapp(N, board);
    vector<vector<int>> isTarget(N, vector<int>(N, 0));
    for(int i=0;i<M;i++){
        isTarget[target[i].first][target[i].second] = 1;
    }
    int step = 0;
    while(seek < M){
        int best_action = -1;
        int best_cost = 1000000;
        // move
        for(int d=0;d<4;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if(board[nx] & (1 << ny)) continue;
            int cost = minCost(nx, ny, seek, target, board, warp);
            if(cost < best_cost){
                best_cost = cost;
                best_action = d;
            }
        }
        // slip
        for(int d=0;d<4;d++){
            int nx = d%2 == 0 ? warp[d][x][y] : x;
            int ny = d%2 == 1 ? warp[d][x][y] : y;
            if(board[nx] & (1 << ny)) continue;
            int cost = minCost(nx, ny, seek, target, board, warp);
            if(cost < best_cost){
                best_cost = cost;
                best_action = d + 4;
            }
        }
        // action
        for(int d=0;d<4;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if(isTarget[nx][ny]) continue;
            board[nx] ^= (1 << ny);
            int cost = minCost(x, y, seek, target, board);
            if(cost < best_cost){
                best_cost = cost;
                best_action = d + 8;
            }
            board[nx] ^= (1 << ny);
        }
        if(best_action < 4){
            x += dx[best_action];
            y += dy[best_action];
        }
        else if(best_action < 8){
            x = best_action%2 == 0 ? warp[best_action%4][x][y] : x;
            y = best_action%2 == 1 ? warp[best_action%4][x][y] : y;
        }
        else{
            int nx = x + dx[best_action-8];
            int ny = y + dy[best_action-8];
            board[nx] ^= (1 << ny);
            warp = genWapp(N, board);
        }
        if(x == target[seek].first && y == target[seek].second){
            seek++;
        }
        cout << "MSA"[best_action/4] << " " << "DRUL"[best_action%4] << endl;
    }

    return 0;
}