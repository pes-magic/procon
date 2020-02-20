#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> Zalgorithm(auto S){
    vector<int> res(S.size());
    res[0] = S.size();
    int i = 1, j = 0;
    while (i < S.size()) {
        while (i+j < S.size() && S[j] == S[i+j]) ++j;
        res[i] = j;
        if (j == 0) { ++i; continue;}
        int k = 1;
        while (i+k < S.size() && k+res[k] < j) res[i+k] = res[k], ++k;
        i += k; j -= k;
    }
    return res;
}

int solve(const string& s , const string& t){
    string u = t + s;
    while(u.size() < s.size() + 2 * t.size()) u += s;
    vector<int> zlen = Zalgorithm(u);
    vector<int> check(s.size(), -1);
    for(int i=0;i<s.size();i++){
        if(zlen[t.size() + i] < t.size()) check[i] = 0;
    }
    for(int i=0;i<s.size();i++){
        if(check[i] != -1) continue;
        vector<int> visit;
        int pos = i;
        while(zlen[t.size() + pos] >= t.size()){
            visit.push_back(pos);
            pos = (pos + t.size()) % s.size();
            if(pos == i) return -1;
            if(check[pos] != -1) break;
        }
        for(int j=visit.size()-1;j>=0;j--){
            check[visit[j]] = check[(visit[j] + t.size())%s.size()] + 1;
        }
    }
    return *max_element(check.begin(), check.end());
}

int main(){
    string s, t;
    while(cin >> s >> t){
        cout << solve(s, t) << endl;
    }
}