#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> solve(const vector<int>& _P){
    auto P = _P;
    vector<int> res;
    const int N = P.size();
    while(true){
        int onePos;
        for(int i=0;i<N;i++) if(P[i] == 1) onePos = i;
        int len = 1;
        for(int i=2;i<N;i++){
            if(P[(onePos+i-1)%N] != i) break;
            ++len;
        }
        if(len == N-1 && onePos == 1) break;
        for(int i=0;i<len;i++){
            res.push_back(onePos);
            swap(P[onePos], P[(onePos+P[onePos])%N]);
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
