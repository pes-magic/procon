#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        map<string, int> mp;
        int m = 0;
        for(int i=0;i<N;i++){
            string s; cin >> s;
            if(!mp.count(s)) mp[s] = 0;
            ++mp[s];
            m = max(m, mp[s]);
        }
        vector<string> vs;
        for(auto it : mp){
            if(it.second == m) vs.push_back(it.first);
        }
        sort(vs.begin(), vs.end());
        for(auto& s : vs) cout << s << endl;
    }
}