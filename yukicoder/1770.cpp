#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> solve(int N, int K){
    vector<vector<int>> pushVal(N);
    vector<vector<int>> popVal(N);
    vector<int> lose(N, 0);
    set<int> loseIdx;
    for(int i=N-1;i>0;i--){
        for(auto& t : pushVal[i]) loseIdx.insert(t);
        for(auto& t : popVal[i]) loseIdx.erase(t);
        if(loseIdx.empty()){
            lose[i] = -1;
            pushVal[i-1].push_back(i);
            if(i-K-1 > 0) popVal[i-K-1].push_back(i);
        } else if(loseIdx.size() == 1){
            int loseK = *loseIdx.begin() - i;
            lose[i] = loseK;
            if(i-loseK > 0) pushVal[i-loseK].push_back(i);
            if(i-loseK-1 > 0) popVal[i-loseK-1].push_back(i);
        } else {
            lose[i] = 0;
        }
    }
    vector<int> res;
    for(int i=1;i<=K;i++){
        if(lose[i] == -1 || lose[i] == i) res.push_back(i);
    }
    return res;
}

int main(){
    int N, K;
    while(cin >> N >> K){
        auto res = solve(N, K);
        if(res.empty()){
            cout << 0 << endl;
        } else {
            for(auto& t : res) cout << t << endl;
        }
    }
}