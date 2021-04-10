#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

int solve(vector<string> vs){
    int res = 0;
    for(int i=0;i+1<vs.size();i++){
        if(vs[i].size() < vs[i+1].size()) continue;
        if(vs[i].size() == vs[i+1].size()){
            if(vs[i] < vs[i+1]) continue;
            ++res;
            vs[i+1] += "0";
        } else {
            bool small = false;
            bool large = false;
            for(int j=0;j<vs[i+1].size();j++){
                if(vs[i][j] == vs[i+1][j]) continue;
                if(vs[i][j] < vs[i+1][j]){
                    large = true;
                    break;
                } else {
                    small = true;
                    break;
                }
            }
            if(small){
                res += vs[i].size() - vs[i+1].size() + 1;
                while(vs[i].size() >= vs[i+1].size()) vs[i+1] += "0";
            } else if(large) {
                res += vs[i].size() - vs[i+1].size();
                while(vs[i].size() > vs[i+1].size()) vs[i+1] += "0";
            } else {
                int pos = -1;
                for(int j=vs[i+1].size();j<vs[i].size();j++){
                    if(vs[i][j] != '9') pos = j;
                }
                if(pos == -1){
                    res += vs[i].size() - vs[i+1].size() + 1;
                    while(vs[i].size() >= vs[i+1].size()) vs[i+1] += "0";
                } else {
                    res += vs[i].size() - vs[i+1].size();
                    for(int j=vs[i+1].size();j<pos;j++){
                        vs[i+1] += vs[i][j];
                    }
                    vs[i+1] += vs[i][pos] + 1;
                    while(vs[i].size() > vs[i+1].size()) vs[i+1] += "0";
                }
            }
        }
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        int N; cin >> N;
        vector<string> vs(N);
        for(auto& s : vs) cin >> s;
        printf("Case #%d: %d\n", i, solve(vs));
    }
}
