#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int H, W;
    while(cin >> H >> W){
        vector<string> vs(H);
        for(auto& s : vs) cin >> s;
        vector<vector<string>> res(2, vector<string>(H, string(W, '.')));
        for(int i=0;i<2;i++){
            for(int j=0;j<H;j++){
                res[i][j][i==0?0:W-1] = '#';
                for(int k=1;k<W-1;k++){
                    if(j%2 == i || vs[j][k]=='#') res[i][j][k] = '#';
                }
            }
        }
        for(int i=0;i<2;i++){
            for(auto& s : res[i]) cout << s << endl;
            if(i==0) cout << endl;
        }
    }
}