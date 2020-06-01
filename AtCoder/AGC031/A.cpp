#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    vector<long long> cnt(26, 1);
    for(auto& c : S) cnt[c-'a']++;
    long long res = 1;
    for(auto& v : cnt) res = (res * v) % MOD;
    res = (res + MOD - 1) % MOD;
    cout << res << endl;
}