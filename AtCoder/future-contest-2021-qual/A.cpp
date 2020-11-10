#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <functional>
#include <cstdlib>

using namespace std;

class Timer {
public:
	explicit Timer()
		: mStart(chrono::system_clock::now())
	{}
	void start() { mStart = chrono::system_clock::now(); }
	double sec() const {
		auto t = chrono::system_clock::now();
		return 1e-6 * chrono::duration_cast<std::chrono::microseconds>(t - mStart).count();
	}
private:
	chrono::system_clock::time_point mStart;
};

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

string naive(const vector<int>& x, const vector<int>& y){
    string s = "";
    int curX = 0, curY = 0;
    for(int i=0;i<100;i++){
        if(curX < x[i]) s += string(x[i] - curX, 'D');
        else if(curX > x[i]) s += string(curX - x[i], 'U');
        if(curY < y[i]) s += string(y[i] - curY, 'R');
        else if(curY > y[i]) s += string(curY - y[i], 'L');
        s += "I";
        curX = x[i];
        curY = y[i];
    }
    return s;
}

string solve(const vector<int>& _x, const vector<int>& _y, int startX = 0, int startY = 0){
    auto x = _x;
    auto y = _y;
    vector<vector<int>> board(20, vector<int>(20, -1));
    for(int i=0;i<100;i++){
        board[x[i]][y[i]] = i;
    }
    const int INF = 1000000;
    vector<int> dp(20*20*101*101);
    vector<int> prev(20*20*101*101);
    int curX = startX, curY = startY;
    auto toIdx = [](int px, int py, int s0, int s1){ return ((px*20+py)*101+s0)*101+s1; };
    auto getX = [](int idx){ return idx/101/101/20; };
    auto getY = [](int idx){ return idx/101/101%20; };
    auto getS0 = [](int idx){ return idx/101%101; };
    auto getS1 = [](int idx){ return idx%101; };
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, -1, 0, 1};
    string res = "";
    for(int i=0;i<100;i++){
        fill(dp.begin(), dp.end(), INF);
        const int startIdx = toIdx(curX, curY, 100, 100);
        dp[toIdx(curX, curY, 100, 100)] = 0;
        priority_queue<int, vector<int>, function<bool(int, int)>> qu(
            [&](int a, int b){
                if(dp[a] != dp[b]) return dp[a] > dp[b];
                return getS0(a) == 100;

            }
        );
        qu.emplace(startIdx);
        while(!qu.empty()){
            int idx = qu.top(); qu.pop();
            const int cx = getX(idx);
            const int cy = getY(idx);
            const int s0 = getS0(idx);
            const int s1 = getS1(idx);
            // move
            for(int j=0;j<4;j++){
                if((x[i] - curX) * dx[j] <= 0 && (y[i] - curY) * dy[j] <= 0) continue;
                const int nx = cx + dx[j];
                const int ny = cy + dy[j];
                if(nx < 0 || 20 <= nx || ny < 0 || 20 <= ny) continue;
                int nextIdx = toIdx(nx, ny, s0, s1);
                if(dp[nextIdx] <= dp[idx] + 1) continue;
                dp[nextIdx] = dp[idx] + 1;
                prev[nextIdx] = idx;
                qu.push(nextIdx);
            }
            // in
            if(board[cx][cy] > i){
                if(s0 == 100){
                    int nextIdx = toIdx(cx, cy, board[cx][cy], s1);
                    if(dp[nextIdx] > dp[idx]){
                        dp[nextIdx] = dp[idx];
                        prev[nextIdx] = idx;
                        qu.push(nextIdx);
                    }
                }
                else if(s1 == 100 && s0 != board[cx][cy]){
                    int nextIdx = toIdx(cx, cy, s0, board[cx][cy]);
                    if(dp[nextIdx] > dp[idx]){
                        dp[nextIdx] = dp[idx];
                        prev[nextIdx] = idx;
                        qu.push(nextIdx);
                    }
                }
            }
            // out
            if(board[cx][cy] == -1){
                if(s1 != 100){
                    int hold = s1;
                    int curCost = abs(x[hold] - x[hold-1]) + abs(y[hold] - y[hold-1]);
                    int newCost = abs(cx - x[hold-1]) + abs(cy - y[hold-1]);
                    if(hold+1 < 100){
                        curCost += abs(x[hold] - x[hold+1]) + abs(y[hold] - y[hold+1]);
                        newCost += abs(cx - x[hold+1]) + abs(cy - y[hold+1]);
                    }
                    for(int j=0;j<4;j++){
                        if((x[i] - curX) * dx[j] <= 0 && (y[i] - curY) * dy[j] <= 0) continue;
                        const int nx = cx + dx[j];
                        const int ny = cy + dy[j];
                        if(nx < 0 || 20 <= nx || ny < 0 || 20 <= ny) continue;
                        int nextIdx = toIdx(nx, ny, s0, 100);
                        if(dp[nextIdx] <= dp[idx] + 1 + newCost - curCost) continue;
                        dp[nextIdx] = dp[idx] + 1 + newCost - curCost;
                        prev[nextIdx] = idx;
                        qu.push(nextIdx);
                    }
                } else if(s0 != 100){
                    int nextIdx = toIdx(cx, cy, 100, s1);
                    int hold = s0;
                    int curCost = abs(x[hold] - x[hold-1]) + abs(y[hold] - y[hold-1]);
                    int newCost = abs(cx - x[hold-1]) + abs(cy - y[hold-1]);
                    if(hold+1 < 100){
                        curCost += abs(x[hold] - x[hold+1]) + abs(y[hold] - y[hold+1]);
                        newCost += abs(cx - x[hold+1]) + abs(cy - y[hold+1]);
                    }
                    if(dp[nextIdx] > dp[idx] + newCost - curCost){
                        dp[nextIdx] = dp[idx] + newCost - curCost;
                        prev[nextIdx] = idx;
                        qu.push(nextIdx);
                    }
                }
            }
        }
        int endIdx = toIdx(x[i], y[i], 100, 100);
        assert(dp[endIdx] != INF);
        int idx = endIdx;
        vector<int> step;
        step.push_back(idx);
        while(idx != startIdx){
            idx = prev[idx];
            step.push_back(idx);
        }
        for(int j=step.size()-1;j-1>=0;j--){
            const int cx = getX(step[j]);
            const int cy = getY(step[j]);
            const int cs = getS0(step[j]);
            const int cs1 = getS1(step[j]);
            const int nx = getX(step[j-1]);
            const int ny = getY(step[j-1]);
            const int ns = getS0(step[j-1]);
            const int ns1 = getS1(step[j-1]);
            if(cs1 != 100 && ns1 == 100){
                res += 'O';
                board[x[cs1]][y[cs1]] = -1;
                board[cx][cy] = cs1;
                x[cs1] = cx;
                y[cs1] = cy;
            }
            if(cx != nx){
                res += (cx < nx ? 'D' : 'U');
            } else if(cy != ny){
                res += (cy < ny ? 'R' : 'L');
            } else if ((cs == 100 && ns != 100) || (cs1 == 100 && ns1 != 100)){
                res += 'I';
            } else {
                res += 'O';
                board[x[cs]][y[cs]] = -1;
                board[cx][cy] = cs;
                x[cs] = cx;
                y[cs] = cy;
            }
        }
        res += 'I';
        board[x[i]][y[i]] = -1;
        curX = x[i];
        curY = y[i];
    }
    return res;
}

double highTemp = 4.979906972778812;
double lowTemp = 0.04497702913927723;
double tempMove = 0.864176222096778;
int ITER = 10000;

string anneal(const vector<int>& _x, const vector<int>& _y){
    auto x = _x;
    auto y = _y;
    vector<int> firstOrder;
    vector<int> putX(100), putY(100);
    vector<vector<int>> board(20, vector<int>(20, -1));
    for(int i=0;i<100;i++){
        if(x[i] >= 10 && y[i] >= 10){
            putX[i] = x[i];
            putY[i] = y[i];
        } else {
            firstOrder.push_back(i);
        }
        board[x[i]][y[i]] = i;
    }
    int idx = 0;
    for(int px=10;px<20;px++){
        for(int py=10;py<20;py++){
            if(board[px][py] == -1){
                board[px][py] = firstOrder[idx];
                putX[firstOrder[idx]] = px;
                putY[firstOrder[idx]] = py;
                ++idx;
            }
        }
    }
    int curBest = 0;
    vector<int> bestFirstOrder = firstOrder;
    vector<int> bestPutX = putX;
    vector<int> bestPutY = putY;
    int curX = 0, curY = 0;
    for(auto& t : firstOrder){
        curBest += abs(x[t] - curX) + abs(y[t] - curY);
        curX = x[t];
        curY = y[t];
    }
    for(int i=firstOrder.size()-1;i>=0;i--){
        curBest += abs(curX - putX[firstOrder[i]]) + abs(curY - putY[firstOrder[i]]);
        curX = putX[firstOrder[i]];
        curY = putY[firstOrder[i]];
    }
    for(int i=0;i<100;i++){
        curBest += abs(curX - putX[i]) + abs(curY - putY[i]);
        curX = putX[i];
        curY = putY[i];
    }
    XorShift gen(1000000007);
    int curScore = curBest;
    auto typeGen = uniform_int_distribution<int>(0, 1);
    auto orderGen = uniform_int_distribution<int>(1, firstOrder.size()-2);
    auto probGen = uniform_real_distribution<>(0.0, 1.0);
    Timer timer;
    const double timeLimit = 2.0;
    while(timer.sec() < timeLimit){
        const double curTemp = highTemp + pow(timer.sec()/timeLimit, tempMove) * (lowTemp - highTemp);
        for(int _=0;_<ITER;_++){
            int a = 0, b = 0;
            while(a == b){
                a = orderGen(gen);
                b = orderGen(gen);
            }
            if(a > b) swap(a, b);
            int type = typeGen(gen);
            if(type == 0){
                int newScore = curScore;
                if(a == 0){
                    newScore -= x[firstOrder[a]] + y[firstOrder[a]];
                    newScore -= abs(putX[firstOrder[a]] - putX[0]) + abs(putY[firstOrder[a]] - putY[0]);
                    newScore += x[firstOrder[b]] + y[firstOrder[b]];
                    newScore += abs(putX[firstOrder[b]] - putX[0]) + abs(putY[firstOrder[b]] - putY[0]);
                } else {
                    newScore -= abs(x[firstOrder[a]] - x[firstOrder[a-1]]) + abs(y[firstOrder[a]] - y[firstOrder[a-1]]);
                    newScore -= abs(putX[firstOrder[a]] - putX[firstOrder[a-1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[a-1]]);
                    newScore += abs(x[firstOrder[b]] - x[firstOrder[a-1]]) + abs(y[firstOrder[b]] - y[firstOrder[a-1]]);
                    newScore += abs(putX[firstOrder[b]] - putX[firstOrder[a-1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[a-1]]);
                }
                if(b == firstOrder.size()-1){
                    newScore -= abs(x[firstOrder[b]] - putX[firstOrder[b]]) + abs(y[firstOrder[b]] - putY[firstOrder[b]]);
                    newScore += abs(x[firstOrder[a]] - putX[firstOrder[a]]) + abs(y[firstOrder[a]] - putY[firstOrder[a]]);
                } else {
                    newScore -= abs(x[firstOrder[b]] - x[firstOrder[b+1]]) + abs(y[firstOrder[b]] - y[firstOrder[b+1]]);
                    newScore -= abs(putX[firstOrder[b]] - putX[firstOrder[b+1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[b+1]]);
                    newScore += abs(x[firstOrder[a]] - x[firstOrder[b+1]]) + abs(y[firstOrder[a]] - y[firstOrder[b+1]]);
                    newScore += abs(putX[firstOrder[a]] - putX[firstOrder[b+1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[b+1]]);
                }
                if(curScore > newScore || probGen(gen) < exp((curScore - newScore)/curTemp)){
                    curScore = newScore;
                    reverse(firstOrder.begin()+a, firstOrder.begin()+b+1);
                    if(curBest > curScore){
                        curBest = curScore;
                        bestFirstOrder = firstOrder;
                    }
                }
            } else {
                int newScore = curScore;
                if(a == 0){
                    newScore -= abs(putX[firstOrder[a]] - putX[0]) + abs(putY[firstOrder[a]] - putY[0]);
                    newScore += abs(putX[firstOrder[b]] - putX[0]) + abs(putY[firstOrder[b]] - putY[0]);
                    if(a+1 != b){
                        newScore -= abs(putX[firstOrder[a]] - putX[firstOrder[a+1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[a+1]]);
                        newScore += abs(putX[firstOrder[b]] - putX[firstOrder[a+1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[a+1]]);
                    }
                } else {
                    newScore -= abs(putX[firstOrder[a]] - putX[firstOrder[a-1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[a-1]]);
                    newScore += abs(putX[firstOrder[b]] - putX[firstOrder[a-1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[a-1]]);
                    if(a+1 != b){
                        newScore -= abs(putX[firstOrder[a]] - putX[firstOrder[a+1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[a+1]]);
                        newScore += abs(putX[firstOrder[b]] - putX[firstOrder[a+1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[a+1]]);
                    }
                }
                if(b == firstOrder.size() - 1){
                    newScore -= abs(x[firstOrder[b]] - putX[firstOrder[b]]) + abs(y[firstOrder[b]] - putY[firstOrder[b]]);
                    newScore += abs(x[firstOrder[b]] - putX[firstOrder[a]]) + abs(y[firstOrder[b]] - putY[firstOrder[a]]);
                    if(b-1 != a){
                        newScore -= abs(putX[firstOrder[b]] - putX[firstOrder[b-1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[b-1]]);
                        newScore += abs(putX[firstOrder[a]] - putX[firstOrder[b-1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[b-1]]);
                    }
                } else {
                    if(b-1 != a){
                        newScore -= abs(putX[firstOrder[b]] - putX[firstOrder[b-1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[b-1]]);
                        newScore += abs(putX[firstOrder[a]] - putX[firstOrder[b-1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[b-1]]);
                    }
                    newScore -= abs(putX[firstOrder[b]] - putX[firstOrder[b+1]]) + abs(putY[firstOrder[b]] - putY[firstOrder[b+1]]);
                    newScore += abs(putX[firstOrder[a]] - putX[firstOrder[b+1]]) + abs(putY[firstOrder[a]] - putY[firstOrder[b+1]]);
                }
                int v0 = firstOrder[a];
                int v1 = firstOrder[b];
                if(v0 > 0 && v1 != v0-1){
                    newScore -= abs(putX[v0] - putX[v0-1]) + abs(putY[v0] - putY[v0-1]);
                    newScore += abs(putX[v1] - putX[v0-1]) + abs(putY[v1] - putY[v0-1]);
                }
                if(v0 < 99 && v1 != v0+1){
                    newScore -= abs(putX[v0] - putX[v0+1]) + abs(putY[v0] - putY[v0+1]);
                    newScore += abs(putX[v1] - putX[v0+1]) + abs(putY[v1] - putY[v0+1]);
                }
                if(v1 > 0 && v0 != v1-1){
                    newScore -= abs(putX[v1] - putX[v1-1]) + abs(putY[v1] - putY[v1-1]);
                    newScore += abs(putX[v0] - putX[v1-1]) + abs(putY[v0] - putY[v1-1]);
                }
                if(v1 < 99 && v0 != v1+1){
                    newScore -= abs(putX[v1] - putX[v1+1]) + abs(putY[v1] - putY[v1+1]);
                    newScore += abs(putX[v0] - putX[v1+1]) + abs(putY[v0] - putY[v1+1]);
                }
                if(curScore > newScore || probGen(gen) < exp((curScore - newScore)/curTemp)){
                    curScore = newScore;
                    swap(putX[v0], putX[v1]);
                    swap(putY[v0], putY[v1]);
                    if(curBest > curScore){
                        curBest = curScore;
                        bestPutX = putX;
                        bestPutY = putY;
                    }
                }
            }
        }
    }
    string res = "";
    curX = 0, curY = 0;
    for(auto& t : bestFirstOrder){
        if(curX < x[t]) res += string(x[t]-curX, 'D');
        if(curX > x[t]) res += string(curX-x[t], 'U');
        if(curY < y[t]) res += string(y[t]-curY, 'R');
        if(curY > y[t]) res += string(curY-y[t], 'L');
        res += 'I';
        curX = x[t];
        curY = y[t];
    }
    for(int i=bestFirstOrder.size()-1;i>=0;i--){
        if(curX < bestPutX[bestFirstOrder[i]]) res += string(bestPutX[bestFirstOrder[i]]-curX, 'D');
        if(curX > bestPutX[bestFirstOrder[i]]) res += string(curX-bestPutX[bestFirstOrder[i]], 'U');
        if(curY < bestPutY[bestFirstOrder[i]]) res += string(bestPutY[bestFirstOrder[i]]-curY, 'R');
        if(curY > bestPutY[bestFirstOrder[i]]) res += string(curY-bestPutY[bestFirstOrder[i]], 'L');
        res += 'O';
        curX = bestPutX[bestFirstOrder[i]];
        curY = bestPutY[bestFirstOrder[i]];
    }
    res += solve(bestPutX, bestPutY, curX, curY);
    return res;
}

int main(int argc, char *argv[]){
    if(argc >= 2) highTemp = atof(argv[1]);
    if(argc >= 3) lowTemp = atof(argv[2]);
    if(argc >= 4) tempMove = atof(argv[3]);
    if(argc >= 5) ITER = (int)atof(argv[4]);
    vector<int> x(100), y(100);
    for(int i=0;i<100;i++) cin >> x[i] >> y[i];
    cout << anneal(x, y) << endl;
}
