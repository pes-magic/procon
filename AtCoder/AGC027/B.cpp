#include <iostream>
#include <vector>

using namespace std;

int main(){
    long long N, X; cin >> N >> X;
    vector<long long> x(N);
    vector<long long> s(N+1, 0);
    for(auto& t : x) cin >> t;
    for(int i=0;i<N;i++) s[i+1] = s[i] + x[i];
    long long res = (1LL << 60);
    for(int i=N;i>=1;i--){
        long long cur = (N+i) * X;
        for(int j=0;j*i<N;j++){
            int src = N - j * i;
            int dst = max(0, src - i);
            cur += (s[src] - s[dst]) * max(5, 2*j+3);
            if(cur > res) break;
        }
        res = min(res, cur);
    }
    cout << res << endl;
}