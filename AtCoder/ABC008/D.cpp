#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int mem[32][32][32][32];

int solve(int sx, int ex, int sy, int ey, 
          const vector<int>& x, const vector<int>& y, 
          const vector<int>& xlist, const vector<int>& ylist)
{
    if(mem[sx][ex][sy][ey] != -1) return mem[sx][ex][sy][ey];
    int& res = mem[sx][ex][sy][ey];
    res = 0;
    for(int i=0;i<x.size();i++){
        if(x[i] <= sx || ex <= x[i] || y[i] <= sy || ey <= y[i]) continue;
        int cur = xlist[ex] - xlist[sx] + ylist[ey] - ylist[sy] - 3;
        cur += solve(sx, x[i], sy, y[i], x, y, xlist, ylist);
        cur += solve(sx, x[i], y[i], ey, x, y, xlist, ylist);
        cur += solve(x[i], ex, sy, y[i], x, y, xlist, ylist);
        cur += solve(x[i], ex, y[i], ey, x, y, xlist, ylist);
        if(res < cur) res = cur;
    }
    return res;
}

int main(){
    int W, H;
    while(cin >> W >> H){
        vector<int> xlist, ylist;
        xlist.push_back(0);
        xlist.push_back(W+1);
        ylist.push_back(0);
        ylist.push_back(H+1);
        int N; cin >> N;
        vector<int> x(N), y(N);
        for(int i=0;i<N;i++){
            cin >> x[i] >> y[i];
            xlist.push_back(x[i]);
            ylist.push_back(y[i]);            
        }
        sort(xlist.begin(), xlist.end());
        sort(ylist.begin(), ylist.end());
        for(int i=0;i<x.size();i++){
            for(int j=0;j<xlist.size();j++){
                if(x[i] == xlist[j]){ x[i] = j; break; }
            }
        }
        for(int i=0;i<y.size();i++){
            for(int j=0;j<ylist.size();j++){
                if(y[i] == ylist[j]){ y[i] = j; break; }
            }
        }
        memset(mem, -1, sizeof(mem));
        cout << solve(0, N+1, 0, N+1, x, y, xlist, ylist) << endl;
    }
}
