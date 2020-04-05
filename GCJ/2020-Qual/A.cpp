#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
    int T; cin >> T;
    for(int caseNum=1;caseNum<=T;caseNum++){
        int N; cin >> N;
        vector<vector<int>> m(N, vector<int>(N));
        for(auto& v : m){
            for(auto& t : v) cin >> t;
        }
        int a = 0, b = 0, c = 0;
        for(int i=0;i<N;i++) a += m[i][i];
        for(int i=0;i<N;i++){
            vector<int> used(N, 0);
            bool ok = true;
            for(int j=0;j<N;j++){
                if(used[m[i][j]-1]) ok = false;
                used[m[i][j]-1] = 1;
            }
            if(!ok) ++b;
        }
        for(int j=0;j<N;j++){
            vector<int> used(N, 0);
            bool ok = true;
            for(int i=0;i<N;i++){
                if(used[m[i][j]-1]) ok = false;
                used[m[i][j]-1] = 1;
            }
            if(!ok) ++c;
        }
        printf("Case #%d: %d %d %d\n", caseNum, a, b, c);
    }
}