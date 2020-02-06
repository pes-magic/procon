#include <iostream>
#include <vector>

using namespace std;

void solve(vector<vector<int>>& a, int s, int e, int level){
    if(e-s <= 1) return;
    int m = (e+s)/2;
    for(int i=s;i<m;i++){
        for(int j=m;j<e;j++){
            a[i][j] = a[j][i] = level;
        }
    }
    solve(a, s, m, level+1);
    solve(a, m, e, level+1);
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> a(N, vector<int>(N));
        solve(a, 0, N, 1);
        for(int i=0;i<N-1;i++){
            cout << a[i][i+1];
            for(int j=i+2;j<N;j++) cout << " " << a[i][j];
            cout << endl;
        }
    }
}