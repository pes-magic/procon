#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

vector<string> split(const string& s){
    vector<string> res;
    string cur = "";
    for(auto& c : s){
        if(c == '*'){ res.push_back(cur); cur = ""; }
        else cur += c;
    }
    res.push_back(cur);
    return res;
}

bool checkPre(string& s, string& t){
    for(int i=0;i<s.size();i++){
        if(i >= t.size()) return true;
        if(s[i] != t[i]) return false;
    }
    return true;
}

bool checkPost(string& s, string& t){
    for(int i=0;i<s.size();i++){
        if(i >= t.size()) return true;
        if(s[s.size()-1-i] != t[t.size()-1-i]) return false;
    }
    return true;
}

string solve(const vector<string>& vs){
    string pre = "";
    string post = "";
    string res = "";
    for(auto& s : vs){
        auto sp = split(s);
        if(!checkPre(pre, sp[0])) return "*";
        if(!checkPost(post, sp.back())) return "*";
        if(pre.size() < sp[0].size()) pre = sp[0];
        if(post.size() < sp.back().size()) post = sp.back();
        for(int i=1;i<sp.size()-1;i++) res += sp[i];
    }
    return pre + res + post;
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        int N; cin >> N;
        vector<string> vs(N);
        for(auto& s : vs) cin >> s;
        printf("Case #%d: %s\n", i, solve(vs).c_str());
    }
}