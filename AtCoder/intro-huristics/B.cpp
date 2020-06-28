#include <iostream>
#include <vector>

using namespace std;

int main(){
    int D; cin >> D;
    vector<int> c(26, 0);
    for(auto& t : c) cin >> t;
    vector s(D, vector(26, 0));
    for(auto& v : s){
        for(auto& t : v) cin >> t;
    }
    vector<int> last(26, 0);
    long long score = 0;
    for(int i=1;i<=D;i++){
        int t; cin >> t;
        --t;
        score += s[i-1][t];
        last[t] = i;
        for(int j=0;j<26;j++){
            score -= c[j] * (i - last[j]);
        }
        cout << score << endl;
    }
}