#include <iostream>
#include <vector>
#include <string>

using namespace std;

string solve(const vector<string>& s){
    const int N = s.size();
    string res(N, '?');
    for(int i=0;i<=N-1-i;i++){
        char c = ' ';
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                if(s[i][j] == s[N-1-i][k]) c = s[i][j];
            }
        }
        if(c == ' ') return "-1";
        res[i] = res[N-1-i] = c;
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<string> vs(N);
    for(auto& s : vs) cin >> s;
    cout << solve(vs) << endl;
}
