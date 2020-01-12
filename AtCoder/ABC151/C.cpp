#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<int> cntWA(N+1, 0);
        vector<int> solve(N+1, 0);
        int wa = 0, ac = 0;
        for(int i=0;i<M;i++){
            int p; string S;
            cin >> p >> S;
            if(S == "WA") ++cntWA[p];
            else {
                if(!solve[p]){
                    solve[p] = 1;
                    ac++;
                    wa += cntWA[p];
                }
            }
        }
        cout << ac << " " << wa << endl;
    }
}