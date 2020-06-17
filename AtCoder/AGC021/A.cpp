#include <iostream>
#include <string>

using namespace std;

int main(){
    string S; cin >> S;
    int res = 0;
    for(auto& c : S) res += c - '0';
    for(int i=0;i<S.size();i++){
        if(S[i] == '0') continue;
        int cur = 0;
        for(int j=0;j<S.size();j++){
            if(j < i) cur += S[j] - '0';
            else if(j == i) cur += S[j] - '0'  - 1;
            else cur += 9;
        }
        res = max(cur, res);
    }
    cout << res << endl;
}