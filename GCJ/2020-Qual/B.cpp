#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

string solve(const string& S){
    int cur = 0;
    string res = "";
    for(auto& c : S){
        int d = c - '0';
        if(cur < d) res += string(d-cur, '(');
        if(cur > d) res += string(cur-d, ')');
        res += c;
        cur = d;
    }
    if(cur > 0) res += string(cur, ')');
    return res;
}

int main(){
    int T; cin >> T;
    for(int caseNum=1;caseNum<=T;caseNum++){
        string S; cin >> S;
        printf("Case #%d: %s\n", caseNum, solve(S).c_str());
    }
}