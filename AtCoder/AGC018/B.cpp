#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<int>> A(N, vector<int>(M));
        for(auto& v : A){
            for(auto& t : v){
                cin >> t;
                --t;
            }
        }
        vector<int> ok(M, 1);
        int best = N;
        for(int i=0;i<M;i++){
            vector<int> cnt(M, 0);
            for(auto& v : A){
                for(int j=0;j<M;j++){
                    if(!ok[v[j]]) continue;
                    cnt[v[j]]++;
                    break;
                }
            }
            int mIdx = 0;
            for(int j=0;j<M;j++){
                if(cnt[j] > cnt[mIdx]) mIdx = j;
            }
            best = min(best, cnt[mIdx]);
            ok[mIdx] = 0;
        }
        cout << best << endl;
    }
}