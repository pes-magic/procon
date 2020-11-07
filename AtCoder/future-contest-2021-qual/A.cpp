#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <functional>

using namespace std;

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

string solve(const vector<int>& _x, const vector<int>& _y){
    auto x = _x;
    auto y = _y;
    vector<vector<int>> board(20, vector<int>(20, -1));
    for(int i=0;i<100;i++){
        board[x[i]][y[i]] = i;
    }
    const int INF = 1000000;
    vector<int> dp(20*20*101*101);
    vector<int> prev(20*20*101*101);
    int curX = 0, curY = 0;
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

int main(){
    vector<int> x(100), y(100);
    for(int i=0;i<100;i++) cin >> x[i] >> y[i];
    cout << solve(x, y) << endl;
}
