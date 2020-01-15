#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string S;
    while(cin >> S){
        vector<long long> cnt(26, 0);
        for(auto& c : S) cnt[c - 'a']++;
        long long res = 0;
        for(int i=0;i<26;i++){
            long long m = 0;
            for(int j=i+1;j<26;j++) m += cnt[j];
            res += cnt[i] * m;
        }
        cout << res + 1 << endl;
    }
}