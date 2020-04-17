#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> solve(int N){
    int ex = (N%2 ? N : N+1);
    vector<pair<int, int>> vp;
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            if(i+j == ex) continue;
            vp.emplace_back(i, j);
        }
    }
    return vp;
}

int main(){
    int N;
    while(cin >> N){
        auto res = solve(N);
        cout << res.size() << endl;
        for(auto& e : res) cout << e.first << " " << e.second << endl;
    }
}