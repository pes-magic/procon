#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<pair<int, int>> solve(const string& S){
    const int N = S.size();
    if(S[0] == '0' || S[N-2] == '0' || S[N-1] == '1') return vector<pair<int, int>>();
    for(int i=0;i<N-2-i;i++){
        if(S[i] != S[N-2-i]) return vector<pair<int, int>>();
    }
    int size = 0;
    int src = 1;
    vector<pair<int, int>> res;
    for(int i=2;i<=N;i++){
        res.emplace_back(src, i);
        if(S[i-2] == '1'){
            src = i;
        }
    }
    return res;
}

int main(){
    string S; cin >> S;
    auto res = solve(S);
    if(res.empty()){
        cout << -1 << endl;
    } else {
        for(auto& p : res) cout << p.first << " " << p.second << endl;
    }
}