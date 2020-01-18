#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int H, W, K;
    while(cin >> H >> W >> K){
        vector<string> a(H);
        for(auto& s : a) cin >> s;
        vector<vector<int>> res(H, vector<int>(W, -1));
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                if(a[i][j] == '#'){
                    res[i][j] = K;
                    --K;
                }
            }
        }
        for(int i=0;i<H;i++){
            for(int j=1;j<W;j++){
                if(res[i][j] != -1) continue;
                res[i][j] = res[i][j-1];
            }
        }
        for(int i=0;i<H;i++){
            for(int j=W-2;j>=0;j--){
                if(res[i][j] != -1) continue;
                res[i][j] = res[i][j+1];
            }
        }
        for(int i=1;i<H;i++){
            for(int j=0;j<W;j++){
                if(res[i][j] != -1) continue;
                res[i][j] = res[i-1][j];
            }
        }
        for(int i=H-2;i>=0;i--){
            for(int j=0;j<W;j++){
                if(res[i][j] != -1) continue;
                res[i][j] = res[i+1][j];
            }
        }
        for(auto& v : res){
            cout << v[0];
            for(int i=1;i<W;i++) cout << " " << v[i];
            cout << endl;
        }
    }
}