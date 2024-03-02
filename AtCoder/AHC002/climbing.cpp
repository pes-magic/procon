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

XorShift rnd(1234567890);

//------------------------------------------------------------------------------
void dfs(int x, int y,
         const vector<vector<int>> &pr,
         const vector<vector<int>> &point,
         vector<vector<int>> &visited,
         int score, vector<pair<int, int>> &step,
         int &bestScore, vector<pair<int, int>> &bestStep,
         int &searchCnt){
    if (searchCnt <= 0) return;
    --searchCnt;
    if(score > bestScore){
        bestScore = score;
        bestStep = step;
    }
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    int ord[] = {0, 1, 2, 3};
    for(int i: ord){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || nx >= 50 || ny < 0 || ny >= 50) continue;
        if(visited[nx][ny]) continue;
        if(pr[nx][ny] != -1){
            int px = pr[nx][ny] / 50;
            int py = pr[nx][ny] % 50;
            visited[px][py] = 1;
        }
        visited[nx][ny] = 1;
        step.push_back({nx, ny});
        dfs(nx, ny, pr, point, visited, score + point[nx][ny], step, bestScore, bestStep, searchCnt);
        visited[nx][ny] = 0;
        step.pop_back();
        if(pr[nx][ny] != -1){
            int px = pr[nx][ny] / 50;
            int py = pr[nx][ny] % 50;
            visited[px][py] = 0;
        }
    }
}

//------------------------------------------------------------------------------
void dfs(int x, int y,
         int gx, int gy,
         const vector<vector<int>> &pr,
         const vector<vector<int>> &point,
         vector<vector<int>> &visited,
         int score, vector<pair<int, int>> &step,
         int &bestScore, vector<pair<int, int>> &bestStep,
         int &searchCnt){
    if (searchCnt <= 0) return;
    --searchCnt;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    int ord[] = {0, 1, 2, 3};
    shuffle(ord, ord + 4, rnd);
    for(int i: ord){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || nx >= 50 || ny < 0 || ny >= 50) continue;
        if(nx == gx && ny == gy){
            if(score > bestScore){
                bestScore = score;
                bestStep = step;
            }
            continue;
        }
        if(visited[nx][ny]) continue;
        if(pr[nx][ny] != -1){
            int px = pr[nx][ny] / 50;
            int py = pr[nx][ny] % 50;
            visited[px][py] = 1;
        }
        visited[nx][ny] = 1;
        step.push_back({nx, ny});
        dfs(nx, ny, gx, gy, pr, point, visited, score + point[nx][ny], step, bestScore, bestStep, searchCnt);
        visited[nx][ny] = 0;
        step.pop_back();
        if(pr[nx][ny] != -1){
            int px = pr[nx][ny] / 50;
            int py = pr[nx][ny] % 50;
            visited[px][py] = 0;
        }
    }
}

//------------------------------------------------------------------------------
int main(){
    int si, sj; cin >> si >> sj;
    vector<vector<int>> A(50, vector<int>(50, 0));
    for(auto &v: A) for(auto &x: v) cin >> x;
    vector<vector<int>> pr(50, vector<int>(50, -1));
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            if(i+1 < 50 && A[i+1][j] == A[i][j]){
                pr[i][j] = 50*(i+1) + j;
                pr[i+1][j] = 50*i + j;
            }
            if(j+1 < 50 && A[i][j+1] == A[i][j]){
                pr[i][j] = 50*i + j+1;
                pr[i][j+1] = 50*i + j;
            }
        }
    }
    vector<vector<int>> point(50, vector<int>(50, 0));
    for(auto& v : point) for(auto& x : v) cin >> x;
    vector<vector<int>> visited(50, vector<int>(50, 0));
    vector<pair<int, int>> step;
    step.push_back({si, sj});
    vector<pair<int, int>> bestStep;
    Timer timer;
    int bestScore = 0;
    visited[si][sj] = 1;
    if(pr[si][sj] != -1){
        int i = pr[si][sj] / 50;
        int j = pr[si][sj] % 50;
        visited[i][j] = 1;
    }
    int seraechCnt = 10000;
    dfs(si, sj, pr, point, visited, 0, step, bestScore, bestStep, seraechCnt);
    for(auto& p : bestStep){
        visited[p.first][p.second] = 1;
        if(pr[p.first][p.second] != -1){
            int px = pr[p.first][p.second] / 50;
            int py = pr[p.first][p.second] % 50;
            visited[px][py] = 1;
        }
    }
    while(timer.msec() < 1900){
        XorShift rnd(chrono::system_clock::now().time_since_epoch().count());
        int s = 0, t = 0;
        while(s == t){
            s = rnd() % (bestStep.size() - 1) + 1;
            t = rnd() % (bestStep.size() - 1) + 1;
        }
        if (s > t) swap(s, t);
        int midBestScore = 0;
        vector<pair<int, int>> midBestStep;
        for(int i=s+1;i<t;i++){
            midBestScore += point[bestStep[i].first][bestStep[i].second];
            midBestStep.push_back(bestStep[i]);
            visited[bestStep[i].first][bestStep[i].second] = 0;
            if(pr[bestStep[i].first][bestStep[i].second] != -1){
                int px = pr[bestStep[i].first][bestStep[i].second] / 50;
                int py = pr[bestStep[i].first][bestStep[i].second] % 50;
                visited[px][py] = 0;
            }
        }

        int searchCnt = (t-s) * 4;
        int curBest = midBestScore;
        step.clear();

        dfs(bestStep[s].first, bestStep[s].second, bestStep[t].first, bestStep[t].second, pr, point, visited, 0, step, midBestScore, midBestStep, searchCnt);
        for(auto& p : midBestStep){
            visited[p.first][p.second] = 1;
            if(pr[p.first][p.second] != -1){
                int px = pr[p.first][p.second] / 50;
                int py = pr[p.first][p.second] % 50;
                visited[px][py] = 1;
            }
        }
        if(midBestScore > curBest){
            vector<pair<int, int>> newBestStep;
            for(int i=0;i<=s;i++) newBestStep.push_back(bestStep[i]);
            for(int i=0;i<midBestStep.size();i++) newBestStep.push_back(midBestStep[i]);
            for(int i=t;i<bestStep.size();i++) newBestStep.push_back(bestStep[i]);
            bestStep = newBestStep;
        }
    }

    for(int i=0;i+1<bestStep.size();i++){
        int dx = bestStep[i+1].first - bestStep[i].first;
        int dy = bestStep[i+1].second - bestStep[i].second;
        if(dx == 0 && dy == 1) cout << "R";
        if(dx == 0 && dy == -1) cout << "L";
        if(dx == 1 && dy == 0) cout << "D";
        if(dx == -1 && dy == 0) cout << "U";
    }
    cout << endl;
}