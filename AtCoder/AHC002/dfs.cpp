#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric>
#include <chrono>
#include <algorithm>

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
void dfs(int x, int y, const vector<vector<int>> &pair, const vector<vector<int>> &point, vector<vector<int>> &visited, int score, string &step, int &bestScore, string& bestStep, Timer &timer){
    if(timer.msec() > 1900) return;
    if(score > bestScore){
        bestScore = score;
        bestStep = step;
    }
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    string s = "LRUD";
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || nx >= 50 || ny < 0 || ny >= 50) continue;
        if(visited[nx][ny]) continue;
        if(pair[nx][ny] != -1){
            int px = pair[nx][ny] / 50;
            int py = pair[nx][ny] % 50;
            visited[px][py] = 1;
        }
        visited[nx][ny] = 1;
        step.push_back(s[i]);
        dfs(nx, ny, pair, point, visited, score + point[nx][ny], step, bestScore, bestStep, timer);
        visited[nx][ny] = 0;
        step.pop_back();
        if(pair[nx][ny] != -1){
            int px = pair[nx][ny] / 50;
            int py = pair[nx][ny] % 50;
            visited[px][py] = 0;
        }
    }
}

//------------------------------------------------------------------------------
int main(){
    int si, sj; cin >> si >> sj;
    vector<vector<int>> A(50, vector<int>(50, 0));
    for(auto &v: A) for(auto &x: v) cin >> x;
    vector<vector<int>> pair(50, vector<int>(50, -1));
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            if(i+1 < 50 && A[i+1][j] == A[i][j]){
                pair[i][j] = 50*(i+1) + j;
                pair[i+1][j] = 50*i + j;
            }
            if(j+1 < 50 && A[i][j+1] == A[i][j]){
                pair[i][j] = 50*i + j+1;
                pair[i][j+1] = 50*i + j;
            }
        }
    }
    vector<vector<int>> point(50, vector<int>(50, 0));
    for(auto& v : point) for(auto& x : v) cin >> x;
    vector<vector<int>> visited(50, vector<int>(50, 0));
    string step = "";
    string bestStep = "";
    Timer timer;
    int bestScore = 0;
    visited[si][sj] = 1;
    if(pair[si][sj] != -1){
        int i = pair[si][sj] / 50;
        int j = pair[si][sj] % 50;
        visited[i][j] = 1;
    }
    dfs(si, sj, pair, point, visited, 0, step, bestScore, bestStep, timer);
    cout << bestStep << endl;
}