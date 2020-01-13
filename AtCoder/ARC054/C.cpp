#include <iostream>
#include <vector>
#include <string>
#include <valarray>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<valarray<int>> M(N, valarray<int>(N));
        for(int i=0;i<N;i++){
            string S; cin >> S;
            for(int j=0;j<N;j++) M[i][j] = S[j] - '0';
        }
        for(int i=0;i<N;i++){
            if(!M[i][i]){
                int idx = -1;
                for(int j=i;j<N;j++){
                    if(M[j][i]){ idx = j; break; }
                }
                if(idx == -1) continue;
                M[i] += M[idx];
                M[i] %= 2;
            }
            for(int j=i+1;j<N;j++){
                if(!M[j][i]) continue;
                M[j] += M[i];
                M[j] %= 2;
            }
        }
        int res = 1;
        for(int i=0;i<N;i++) res *= M[i][i];
        cout << (res ? "Odd" : "Even") << endl;
    }
}