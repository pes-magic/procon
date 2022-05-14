#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<vector<int>> drawA(int R){
    vector<vector<int>> res(R+1, vector<int>(R+1, 0));
    for(int i=0;i<=R;i++){
        for(int j=0;j<=R;j++){
            if(int(sqrt(i*i+j*j)+0.5) <= R) res[i][j] = 1;
        }
    }
    return res;
}


vector<vector<int>> drawB(int R){
    vector<vector<int>> res(R+1, vector<int>(R+1, 0));
    for(int r=0;r<=R;r++){
        for(int x=0;x<=r;x++){
            int y = (int)(sqrt(r*r-x*x)+0.5);
            res[x][y] = res[y][x] = 1;
        }
    }
    return res;
}

// only solves visible input
int solve(int R){
    auto a = drawA(R);
    auto b = drawB(R);
    int res = 0;
    for(int x=1;x<=R;x++){
        for(int y=1;y<=R;y++){
            if(a[x][y] != b[x][y]) res += 4;
        }
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int R; cin >> R;
        cout << "Case #" << t << ": " << solve(R) << endl;
    }
}