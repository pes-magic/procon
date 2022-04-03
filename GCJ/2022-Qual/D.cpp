#include <iostream>
#include <vector>

using namespace std;

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        int N; cin >> N;
        vector<int> F(N);
        for(int i=0;i<N;i++){
            cin >> F[i];
        }
        vector<vector<int>> g(N);
        vector<int> end(N, 0);
        for(int i=0;i<N;i++){
            int p; cin >> p; p--;
            if(p >= 0) g[p].push_back(i);
            else end[i] = 1;
        }
        long long res = 0;
        for(int i=N-1;i>=0;i--){
            int target = 0;
            for(int j=0;j<g[i].size();j++){
                if(F[g[i][j]] < F[g[i][target]]) target = j;
            }
            for(int j=0;j<g[i].size();j++){
                if(j == target){
                    F[i] = max(F[i], F[g[i][j]]);
                } else {
                    res += F[g[i][j]];
                }
            }
            if(end[i]) res += F[i];
        }
        cout << "Case #" << test << ": " << res << endl;
    }
}