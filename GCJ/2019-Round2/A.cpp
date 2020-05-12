#include <iostream>
#include <vector>
#include <set>
#include <cstdio>

using namespace std;

int gcd(int a, int b){ return a%b ? gcd(b, a%b) : b; }

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        vector<pair<int, int>> vp(N);
        for(auto& p : vp) cin >> p.first >> p.second;
        set<pair<int, int>> S;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                int a = vp[i].second - vp[j].second;
                int b = vp[i].first - vp[j].first;
                if(a == 0 || b == 0) continue;
                if(!((a > 0)^(b > 0))) continue;
                a = abs(a);
                b = abs(b);
                int g = gcd(a, b);
                a /= g;
                b /= g;
                S.emplace(a, b);
            }
        }
        printf("Case #%d: %d\n", t, S.size()+1);
    }
}