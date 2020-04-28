#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string S; cin >> S;
    long long res = 0;
    const int N = S.size();
    const int P = 2019;
    int m = 1;
    vector<int> mod(N);
    int val = 0;
    for(int i=N-1;i>=0;i--){
        val += m * (S[i]-'0');
        val %= P;
        mod[i] = val;
        m = 10 * m % P;
    }
    vector<int> cnt(P, 0);
    for(int i=0;i<N;i++){
        ++cnt[mod[i]];
        res += (mod[i] == 0 ? cnt[mod[i]] : cnt[mod[i]] - 1);
    }
    cout << res << endl;
}
