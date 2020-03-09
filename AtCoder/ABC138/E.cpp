#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string s, t;
    while(cin >> s >> t){
        vector<vector<int>> next(26, vector<int>(s.size(), -1));
        const int n = s.size();
        for(int i=0;i<n;i++){
            if(next[s[i]-'a'][i] != -1) continue;
            int p = i;
            for(int j=1;j<=n;j++){
                int idx = (i-j+n)%n;
                next[s[i]-'a'][idx] = p;
                if(s[idx] == s[i]) p = idx;
            }
        }
        long long res = 0;
        int pos = 0;
        bool first = true;
        for(auto& c : t){
            if(first){
                first = false;
                if(c == s[0]) continue;
            }
            if(next[c-'a'][pos] == -1){
                res = -1;
                break;
            }
            if(next[c-'a'][pos] <= pos) ++res;
            pos = next[c-'a'][pos];
        }
        cout << (res < 0 ? -1 : res*n + pos + 1) << endl;
    }
}