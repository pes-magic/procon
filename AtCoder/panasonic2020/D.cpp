#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve(vector<string>& res, string cur, char alpha){
    int cnt = 0;
    vector<int> pos;
    for(int i=0;i<cur.size();i++){
        if(cur[i] == '?'){
            ++cnt;
            if(cnt == 1){
                cur[i] = alpha;
            } else {
                pos.push_back(i);
            }
        }
    }
    if(pos.empty()){
        res.push_back(cur);
        return;
    }
    for(int i=0;i<(1<<pos.size());i++){
        string next = cur;
        for(int j=0;j<pos.size();j++){
            if(i&(1<<j)) next[pos[j]] = alpha;
        }
        solve(res, next, alpha+1);
    }
}

int main(){
    int N;
    while(cin >> N){
        vector<string> res;
        solve(res, string(N, '?'), 'a');
        sort(res.begin(), res.end());
        for(auto& s : res) cout << s << endl;
    }
}