#include <iostream>
#include <vector>
#include <string>

using namespace std;

int gcd(int a, int b){ return a%b ? gcd(b, a%b) : b; }

int solve(const string& S, const vector<vector<int>>& div){
    vector<int> s;
    for(int i=0;i<S.size();i++) if(S[i] == '.') s.push_back(i);
    if(s.size() <= 1) return s.size();
    if(s.size() == 2) return div[s[1]-s[0]].empty() ? 2 : 1;
    int res = 3;
    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){
            for(int d : div[s[j]-s[i]]){
                int a = -1, g = 0;
                for(auto& t : s){
                    if((t-s[i])%d == 0) continue;
                    if(a == -1) a = t;
                    else if(g == 0) g = t-a;
                    else g = gcd(g, t-a);
                }
                if(a == -1) res = 1;
                else {
                    res = min(res, g && div[g].empty() ? 3 : 2);
                }
            }
        }
    }
    return res;
}

int main(){
    vector<vector<int>> div(100001);
    for(int i=3;i<=100000;i+=2){
        if(!div[i].empty()) continue;
        for(int j=i;j<=100000;j+=i) div[j].push_back(i);
    }
    int H, W;
    while(cin >> H >> W){
        int res = 0;
        for(int i=0;i<H;i++){
            string S; cin >> S;
            res += solve(S, div);
        }
        cout << res << endl;
    }
}
