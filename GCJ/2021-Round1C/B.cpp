#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int compare(const string& A, const string& B){
    if(A.size() < B.size()) return -1;
    if(A.size() > B.size()) return 1;
    if(A < B) return -1;
    if(A > B) return 1;
    return 0;
}

string solve(const string& S){
    string res = "1234567891011121314";
    auto gen = [&](long long v){
        string cur = to_string(v);
        for(long long j=v+1;;j++){
            cur.append(to_string(j));
            if(compare(S, cur) == -1) break;
        }
        if(compare(cur, res) == -1) res = cur;
    };
    for(int i=1;i<1000000;i++) gen(i);
    long long val = 1000000;
    gen(1000000);
    gen(9999999);
    gen(10000000);
    gen(99999999);
    gen(100000000);
    for(int j=7;j<S.size();j++){
        gen(stoll(S.substr(0, j)));
        gen(stoll(S.substr(0, j))+1);
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        string S; cin >> S;
        printf("Case #%d: %s\n", i, solve(S).c_str());
    }
}
