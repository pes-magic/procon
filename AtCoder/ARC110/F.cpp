#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> solve(const vector<int>& _P){
    auto P = _P;
    vector<int> res;
    const int N = P.size();
    while(true){
        bool ok = true;
        for(int i=0;i<N;i++) if(P[i] != i) ok = false;
        if(ok) break;
        for(int i=0;i<N;i++){
            if(P[i] != 0 && ((i+P[i])%N == P[i] || i == P[(i+P[i])%N])){
                res.push_back(i);
                swap(P[i], P[(i+P[i])%N]);
                break;
            }
            if(i == N-1){
                int t = rand()%N;
                res.push_back(t);
                swap(P[t], P[(t+P[t])%N]);
            }
        }
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<int> P(N);
    for(auto& t : P) cin >> t;
    auto res = solve(P);
    cout << res.size() << endl;
    for(auto& t : res) cout << t << endl;
}
