#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<string> vs(N);
        for(auto& s : vs) cin >> s;
        vector<vector<int>> cur(N, vector<int>(N));
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) cur[i][j] = (vs[i][j] == '#' ? 1 : 0);
        }
        vector<vector<int>> prev(N, vector<int>(N, 0));
        int di[] = {-2, -1, -1};
        int dj[] = {0, -1, 1};
        for(int i=1;i<N;i++){
            for(int j=0;j<N;j++){
                prev[i][j] = cur[i-1][j];
                for(int d=0;d<3;d++){
                    if(i+di[d] < 0 || N <= i+di[d] || j+dj[d] < 0 || N <= j+dj[d]) continue;
                    prev[i][j] += prev[i+di[d]][j+dj[d]];
                }
                prev[i][j] %= 2;
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) cout << ".#"[prev[i][j]];
            cout << endl;
        }
    }
}