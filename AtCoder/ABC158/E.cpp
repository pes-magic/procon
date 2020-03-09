#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N, P;
    while(cin >> N >> P){
        string S; cin >> S;
        long long res = 0;
        if(P == 2 || P == 5){
            for(int i=0;i<N;i++){
                if((S[i]-'0')%P == 0) res += i+1;
            }
        } else {
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
        }
        cout << res << endl;
    }
}