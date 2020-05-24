#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

static int query_cnt = 0;
const string ans = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890qwer";
const bool is_debug = false;

int query(const vector<char>& vc){
    cout << "? ";
    for(auto& c : vc) cout << char(c);
    cout << endl;
    if(is_debug){
        ++query_cnt;
        vector<vector<int>> dp(ans.size()+1, vector<int>(vc.size()+1, 100000000));
        dp[0][0] = 0;
        for(int i=0;i<=ans.size();i++){
            for(int j=0;j<=vc.size();j++){
                if(j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1]+1);
                if(i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j]+1);
                if(i > 0 && j > 0) dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (ans[i-1] == vc[j-1] ? 0 : 1));
            }
        }
        return dp.back().back();
    }
    int q; cin >> q;
    return q;
}

int main(){
    vector<char> vc;
    for(int i=0;i<10;i++) vc.push_back('0'+i);
    for(int i=0;i<26;i++) vc.push_back('a'+i);
    for(int i=0;i<26;i++) vc.push_back('A'+i);

    int L = 0;
    auto cmp = [](const vector<char>& a, const vector<char>& b){ return a.size() > b.size(); };
    priority_queue<vector<char>, vector<vector<char>>, decltype(cmp)> qu(cmp);
    for(int i=0;i<vc.size();i++){
        vector<char> cur(128, vc[i]);
        int q = query(cur);
        if(q == 128) continue;
        qu.push(vector<char>(128-q, vc[i]));
        L += 128 - q;
    }

    while(qu.size() >= 2){
        auto a = qu.top(); qu.pop();
        auto b = qu.top(); qu.pop();
        swap(b, a);
        int idx = 0;
        int cur = L - a.size();
        for(int i=0;i<b.size();i++){
            a.push_back(b[i]);
            for(int j=a.size()-2;j>=idx;j--) swap(a[j], a[j+1]);
            while(true){
                ++idx;
                if(idx == a.size()) break;
                int q = query(a);
                if(q == L - a.size()) break;
                swap(a[idx-1], a[idx]);
            }
        }
        qu.push(a);
    }
    auto res = qu.top();
    cout << "! ";
    for(auto& c : res) cout << char(c);
    cout << endl;
    if(is_debug){
        string result = "";
        for(auto& c : res) result += c;
        if(ans != result || query_cnt > 850){
            cerr << query_cnt << endl;
            cerr << ans << endl;
            cerr << result << endl;
        }
    }
}
