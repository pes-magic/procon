#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int N, K; cin >> N >> K;
    map<string, int> mp;
    for(int i=0;i<N;i++){
        string S; cin >> S;
        if(!mp.count(S)) mp[S] = 0;
        ++mp[S];
    }
    vector<vector<string>> vs(N+1);
    for(auto& it : mp){
        vs[it.second].push_back(it.first);
    }
    for(int i=N;i>=0;i--){
        if(vs[i].empty()) continue;
        if(K > vs[i].size()){
            K -= vs[i].size();
        } else {
            cout << (vs[i].size() == 1 ? vs[i].front() : "AMBIGUOUS") << endl;
            break;
        }
    }
}
