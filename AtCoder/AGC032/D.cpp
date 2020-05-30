#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1LL << 60;

int main(){
    int N;
    long long A, B;
    cin >> N >> A >> B;
    vector<int> pos(N);
    for(int i=0;i<N;i++){
        int p; cin >> p;
        pos[p-1] = 2*i+1;
    }
    vector<long long> dp(2*N+1, INF);
    for(int i=0;i<pos[0];i+=2) dp[i] = B;
    dp[pos[0]] = 0;
    for(int i=pos[0]+1;i<=2*N;i+=2) dp[i] = A;
    for(int i=1;i<N;i++){
        long long best = INF;
        for(int j=0;j<=2*N;j++){
            best = min(best, dp[j]);
            if(j%2 == 0){
                auto c = (j < pos[i] ? B : A);
                dp[j] = best + c;
            } else if(j == pos[i]){
                dp[j] = best;
            } else {
                dp[j] = INF;
            }
        }
    }
    cout << *min_element(dp.begin(), dp.end()) << endl;
}