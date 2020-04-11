#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

long long solve(const vector<vector<int>>& A){
    const int h = A.size();
    const int w = A[0].size();
    long long sum = 0;
    long long res = 0;
    vector<vector<int>> elim = A;
    vector<vector<int>> preW = A;
    vector<vector<int>> postW = A;
    vector<vector<int>> preH = A;
    vector<vector<int>> postH = A;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            preW[i][j] = j-1;
            postW[i][j] = j+1;
            preH[i][j] = i-1;
            postH[i][j] = i+1;
        }
    }
    vector<pair<int,int>> check;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            sum += A[i][j];
            check.emplace_back(i, j);
        }
    }
    while(!check.empty()){
        res += sum;
        vector<pair<int, int>> next;
        vector<pair<int, int>> del;
        for(auto& p : check){
            int dx[] = {preH[p.first][p.second], p.first, postH[p.first][p.second], p.first};
            int dy[] = {p.second, preW[p.first][p.second], p.second, postW[p.first][p.second]};
            int num = 0;
            int arr = 0;
            for(int d=0;d<4;d++){
                const int nx = dx[d];
                const int ny = dy[d];
                if(nx < 0 || h <= nx || ny < 0 || w <= ny || !elim[nx][ny]) continue;
                arr += A[nx][ny];
                ++num;
            }
            if(num == 0) continue;
            if(arr <= A[p.first][p.second] * num) continue;
            del.push_back(p);
        }
        for(auto& p : del){
            sum -= A[p.first][p.second];
            elim[p.first][p.second] = 0;
        }
        for(auto& p : del){
            int dx[] = {preH[p.first][p.second], p.first, postH[p.first][p.second], p.first};
            int dy[] = {p.second, preW[p.first][p.second], p.second, postW[p.first][p.second]};
            for(int d=0;d<4;d++){
                const int nx = dx[d];
                const int ny = dy[d];
                if(nx < 0 || h <= nx || ny < 0 || w <= ny || !elim[nx][ny]) continue;
                next.emplace_back(nx, ny);
            }
        }
        for(auto& p : del){
            {
                int tpre = preW[p.first][p.second];
                int tpost = postW[p.first][p.second];
                if(0 <= tpre && tpre < w) postW[p.first][tpre] = tpost;
                if(0 <= tpost && tpost < w) preW[p.first][tpost] = tpre;
            }
            {
                int tpre = preH[p.first][p.second];
                int tpost = postH[p.first][p.second];
                if(0 <= tpre && tpre < h) postH[tpre][p.second] = tpost;
                if(0 <= tpost && tpost < h) preH[tpost][p.second] = tpre;
            }
        }
        sort(next.begin(), next.end());
        next.erase(unique(next.begin(), next.end()), next.end());
        check = next;
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int R, C; cin >> R >> C;
        vector<vector<int>> A(R, vector<int>(C));
        for(auto& v : A){
            for(auto& a : v) cin >> a;
        }
        printf("Case #%d: %lld\n", t, solve(A));
    }
}