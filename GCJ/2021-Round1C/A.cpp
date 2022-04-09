#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

double solve(){
    int N, K; cin >> N >> K;
    vector<int> P(N);
    for(auto& t : P) cin >> t;
    sort(P.begin(), P.end());
    vector<int> part;
    int res = 0;
    part.push_back(P.front()-1);
    part.push_back(K-P.back());
    for(int i=0;i+1<P.size();i++){
        res = max(res, P[i+1]-P[i]-1);
        part.push_back((P[i+1]-P[i])/2);
    }
    sort(part.rbegin(), part.rend());
    res = max(res, part[0]+part[1]);
    return (double)res/K;
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        printf("Case #%d: %lf\n", i, solve());
    }
}
