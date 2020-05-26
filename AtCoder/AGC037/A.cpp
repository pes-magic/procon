#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(const string& S){
    const int N = S.size();
    if(N == 1) return 1;
    vector<vector<int>> a(N+2, vector<int>(2, 0));
    a[0][0] = a[1][1] = 1;
    for(int i=0;i<S.size();i++){
        for(int j=0;j<2;j++){
            a[i+2-j][1-j] = max(a[i+2-j][1-j], a[i][j]+1);
            if(j == 0 && i+1 < N && S[i] != S[i+1]) a[i+1][0] = max(a[i+1][0], a[i][j]+1);
            if(j == 1 && i+2 < N && i-1 >= 0 && (S[i-1] != S[i+1] || S[i] != S[i+2])) a[i+2][1] = max(a[i+2][1], a[i][j]+1);
        }
    }
    return max(a[N-1][0], a[N-1][1]);
}

int main(){
    string S; cin >> S;
    cout << solve(S) << endl;
}