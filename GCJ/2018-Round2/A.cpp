#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

vector<string> solve(const vector<int>& b){
    int n = b.size();
    if(b[0] == 0 || b.back() == 0) return vector<string>();
    int s = 0;
    int d = 0;
    for(int i=0;i<n;i++){
        int e = s + b[i] - 1;
        d = max(d, max(i-s, e-i));
        s = e + 1;
    }
    vector<string> res(d+1, string(n, '.'));
    s = 0;
    for(int i=0;i<n;i++){
        int e = s + b[i] - 1;
        if(b[i] > 0){
            if(s < i){
                for(int j=1;i-j>=s;j++){
                    res[d-j][i-j] = '\\';
                }
            }
            if(i < e){
                for(int j=1;i+j<=e;j++){
                    res[d-j][i+j] = '/';
                }
            }
        }
        s = e + 1;
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int C; cin >> C;
        vector<int> b(C);
        for(auto& t : b) cin >> t;
        auto res = solve(b);
        printf("Case #%d: ", t);
        if(res.empty()){
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << res.size() << endl;
            for(auto& s : res) cout << s << endl;
        }
    }
}