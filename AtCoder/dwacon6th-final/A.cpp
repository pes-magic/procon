#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> solve(int H, int W){
    if(H > W) swap(H, W);
    vector<vector<int>> res(H, vector<int>(W));
    if(H > 3) return vector<vector<int>>();
    if(H == 1){
        if(W%7 != 2 && W%7 != 5 && W%7 != 0) return vector<vector<int>>();
        int idx = 0;
        if(W%7 == 2){
            res[0][0] = res[0][1] = 2;
            idx = 2;
        }
        while(idx < W){
            for(int i=0;i<5;i++) res[0][idx++] = 5;
            if(idx == W) break;
            for(int i=0;i<2;i++) res[0][idx++] = 2;
        }
    } else if(H == 2){
        if(W%7 != 1 && W%7 != 6 && W%7 != 0) return vector<vector<int>>();
        int idx = 0;
        if(W%7 == 1){
            res[0][0] = res[1][0] = 2;
            idx = 1;
        }
        int tmp[2][6] = {
            {5, 5, 5, 2, 5, 5},
            {5, 5, 2, 5, 5, 5}
        };
        while(idx < W){
            for(int i=0;i<6;i++){
                res[0][idx] = tmp[0][i];
                res[1][idx] = tmp[1][i];
                ++idx;
            }
            if(idx == W) break;
            res[0][idx] = res[1][idx] = 2;
            ++idx;
        }
    } else if(H == 3){
        if(W != 3) return vector<vector<int>>();
        res[0] = {2, 5, 5};
        res[1] = {2, 5, 2};
        res[2] = {5, 5, 2};
    }
    return res;
}

int main(){
    int H, W;
    while(cin >> H >> W){
        vector<vector<int>> res = solve(H, W);
        cout << (res.empty() ? "No" : "Yes") << endl;
        if(res.size() == H){
            for(auto& v : res){
                for(auto& t : v) cout << t;
                cout << endl;
            }
        } else if(res.size() == W){
            for(int i=0;i<H;i++){
                for(int j=0;j<W;j++) cout << res[j][i];
                cout << endl;
            }
        }
    }
}