#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<vector<int>> getNext(const string& s){
    vector<vector<int>> res(s.size(), vector<int>(26, s.size()));
    vector<int> last(26, s.size()+1);
    for(int i=s.size()-1;i>=0;i--){
        last[s[i]-'a'] = i+1;
        for(int j=0;j<26;j++) res[i][j] = last[j];
    }
    return res;
}

string solve(const string& S, const string& T){
    auto nextS = getNext(S);
    auto nextT = getNext(T);
    vector<int> dp(T.size()+1, S.size());
    for(int i=T.size()-1;i>=0;i--){
        dp[i] = dp[i+1];
        if(dp[i] == 0) continue;
        if(S[dp[i]-1] == T[i]) --dp[i];
    }
    if(dp[0] == 0) return "-1";
    int posS = 0, posT = 0;
    string res = "";
    while(posS < S.size()){
        for(int i=0;i<26;i++){
            int ns = nextS[posS][i];
            int nt = (posT < T.size() ? nextT[posT][i] : T.size()+1);
            if(ns > S.size()) continue;
            if(nt > T.size()){
                res += 'a'+i;
                return res;
            }
            if(dp[nt] > ns){
                res += 'a'+i;
                posS = ns;
                posT = nt;
                break;
            }
        }
    }
    return res;
}

int main(){
    string S, T;
    while(cin >> S >> T){
        cout << solve(S, T) << endl;
    }
}