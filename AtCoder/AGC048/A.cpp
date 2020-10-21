#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

int main(){
    string C = "atcoder";
    int T; cin >> T;
    for(int i=0;i<T;i++){
        string S; cin >> S;
        if(C < S){
            cout << 0 << endl;
        } else {
            int res = INF;
            for(int j=0;j<S.size();j++){
                if(S[j] != 'a'){
                    string U = S;
                    for(int k=j-1;k>=0;k--){
                        swap(U[k], U[k+1]);
                        if(C < U) res = min(j-k, res);
                    }
                }
            }
            cout << (res == INF ? -1 : res) << endl;
        }
    }
}