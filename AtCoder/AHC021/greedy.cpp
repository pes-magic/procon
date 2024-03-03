#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <chrono>

using namespace std;

const int N = 30;

int main(){
    int a[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<=i;j++) cin >> a[i][j];
    }
    vector<vector<int>> best;
    for(int i=0;i<N*(N+1)/2;i++){
        int x, y;
        for(int j=0;j<N;j++){
            for(int k=0;k<=j;k++){
                if(a[j][k] == i){
                    x = j, y = k;
                    break;
                }
            }
        }
        while(true){
            int l = -1, r = -1;
            if(x == 0) break;
            if(0 <= y-1 && y-1 <= x-1) l = a[x-1][y-1];
            if(0 <= y && y <= x-1) r = a[x-1][y];
            if(i > max(l, r)) break;
            if(l > r){
                best.push_back(vector<int>{x, y, x-1, y-1});
                swap(a[x][y], a[x-1][y-1]);
                x--; y--;
            } else {
                best.push_back(vector<int>{x, y, x-1, y});
                swap(a[x][y], a[x-1][y]);
                x--;
            }
        }
    }
    cout << best.size() << endl;
    for(auto p : best){
        cout << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << endl;
    }
}
