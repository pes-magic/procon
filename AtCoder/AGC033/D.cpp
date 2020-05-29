#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int maxN = 185;
char res[maxN*(maxN+1)/2][maxN*(maxN+1)/2];

char solve(const vector<string>& A, int sx, int ex, int sy, int ey){
    int x = sx * (2 * maxN - sx + 1) / 2 + ex - sx;
    int y = sy * (2 * maxN - sy + 1) / 2 + ey - sy;
    if(res[x][y] != -1) return res[x][y];
    if(sx == ex && sy == ey) return res[x][y] = 0;
    char r = 100;
    int L = sx, R = ex + 1;
    while(R-L > 1){
        int mid = (L+R)/2;
        auto c1 = solve(A, sx, mid-1, sy, ey);
        auto c2 = solve(A, mid, ex, sy, ey);
        if(c1 == 0 && c2 == 0 && A[sx][sy] == A[mid][sy]){
            r = 0;
        } else {
            r = min<char>(r, max(c1, c2) + 1);
        }
        if(c1 == c2) break;
        if(c1 > c2) R = mid;
        else L = mid;
    }
    L = sy, R = ey + 1;
    while(R-L > 1){
        int mid = (L+R)/2;
        auto c1 = solve(A, sx, ex, sy, mid-1);
        auto c2 = solve(A, sx, ex, mid, ey);
        if(c1 == 0 && c2 == 0 && A[sx][mid-1] == A[sx][mid]){
            r = 0;
        } else {
            r = min<char>(r, max(c1, c2) + 1);
        }
        if(c1 == c2) break;
        if(c1 > c2) R = mid;
        else L = mid;
    }
    return res[x][y] = r;
}

int main(){
    int H, W; cin >> H >> W;
    vector<string> A(H);
    for(auto& a : A) cin >> a;
    memset(res, -1, sizeof(res));
    cout << (int)solve(A, 0, H-1, 0, W-1) << endl;
}