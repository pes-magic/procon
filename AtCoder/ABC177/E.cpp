#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

string solve(const vector<int>& a){
    int v = a[0];
    for(auto& t : a) v = gcd(v, t);
    if(v > 1) return "not coprime";
    vector<int> m(1000000, 0);
    for(auto& t : a){
        int v = t;
        for(int d=2;d*d<=v;d++){
            if(v%d) continue;
            if(m[d]) return "setwise coprime";
            while(v%d == 0) v /= d;
            m[d] = 1;
        }
        if(v > 1){
            if(m[v]) return "setwise coprime";
            m[v] = 1;
        }
    }
    return "pairwise coprime";
}

int main(){
    int N; cin >> N;
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    cout << solve(a) << endl;
}