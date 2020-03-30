#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string b, price;
    while(cin >> b >> price){
        vector<vector<int>> low(100, vector<int>(100, 0));
        low[0].clear();
        for(int i=0;i<100;i++){
            for(auto& c : b){
                int d = c - '0';
                if(d == 0) continue;
                if(i + d >= 100) continue;
                if(low[i].size() + 1 < low[i+d].size()){
                    low[i+d] = low[i];
                    low[i+d].push_back(d);
                }
            }
        }
        vector<vector<int>> dp(price.size()+1, vector<int>(100, 10000000));
        vector<vector<int>> prev(price.size()+1, vector<int>(100, -1));
        dp[0][0] = 0;
        for(int i=0;i<price.size();i++){
            for(int j=0;j<100;j++){
                int seqNum = j/10;
                int rest = 10*(j%10) + price[i] - '0';
                for(int k=0;k<10;k++){
                    if(rest - k < 0) break;
                    int nsize = max<int>(seqNum, low[rest-k].size());
                    if(nsize >= 10) continue;
                    int inc = nsize - seqNum;
                    int next = dp[i][j] + inc * (price.size() - i + 1) - (seqNum == 0 ? 1 : 0);
                    if(next < dp[i+1][10*nsize+k]){
                        dp[i+1][10*nsize+k] = next;
                        prev[i+1][10*nsize+k] = j;
                    }
                }
            }
        }
        int start = 0;
        for(int i=0;i<100;i+=10) if(dp[price.size()][i] < dp[price.size()][start]) start = i;
        vector<vector<int>> res(start/10);
        for(int i=price.size()-1;i>=0;i--){
            int back = prev[i+1][start];
            int dec = 10*(back%10)+price[i]-'0' - start%10;
            for(int j=0;j<low[dec].size();j++) res[j].push_back(low[dec][j]);
            for(int j=low[dec].size();j<res.size();j++) res[j].push_back(0);
            start = back;
        }
        for(int i=0;i<res.size();i++){
            bool find = false;
            for(int j=res[i].size()-1;j>=0;j--){
                if(res[i][j] != 0) find = true;
                if(find) cout << res[i][j];
            }
            if(res.size() >= 2) cout << (i==res.size()-1 ? "=" : "+");
        }
        cout << endl;
    }
}