#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

string solve(long long x, long long y){
    if(abs(x+y)%2 == 0) return "IMPOSSIBLE";
    long long dx[] = {-1, 0, 1, 0};
    long long dy[] = {0, -1, 0, 1};
    string dir = "WSEN";
    int step = 1;
    while((1LL<<step)-1 < abs(x)+abs(y)) ++step;
    string res = string(step, '?');
    for(int i=step-1;i>=0;i--){
        long long minDist = (1LL << 60);
        long long jump = (1LL << i);
        int minDir = 0;
        for(int j=0;j<4;j++){
            long long curDist = abs(x - dx[j] * jump) + abs(y - dy[j] * jump);
            if(curDist < minDist){
                minDist = curDist;
                minDir = j;
            }
        }
        res[i] = dir[minDir];
        x -= dx[minDir] * jump;
        y -= dy[minDir] * jump;
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int x, y; cin >> x >> y;
        printf("Case #%d: %s\n", t, solve(x, y).c_str());
    }
}