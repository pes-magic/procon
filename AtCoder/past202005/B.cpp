#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M, Q; cin >> N >> M >> Q;
    vector<int> score(M, N);
    vector<vector<int>> solve(N, vector<int>(M, 0));
    for(int i=0;i<Q;i++){
        int t, n; cin >> t >> n;
        if(t == 1){
            int res = 0;
            for(int j=0;j<M;j++) res += solve[n-1][j] * score[j];
            cout << res << endl;
        } else {
            int m; cin >> m;
            score[m-1]--;
            solve[n-1][m-1] = 1;
        }
    }
}
