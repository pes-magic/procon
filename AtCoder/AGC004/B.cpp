#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
    int N;
    long long K;
    cin >> N >> K;
    vector<long long> a(N);
    for(auto& t : a) cin >> t;
    long long res = accumulate(a.begin(), a.end(), 0LL);
    for(int i=0;i<N;i++){
        auto c = a;
        for(int j=0;j<N;j++){
            c[j] = min(c[j], a[(j+N-1)%N]);
        }
        a = c;
        res = min(res, accumulate(a.begin(), a.end(), 0LL) + (i+1) * K);
    }
    cout << res << endl;
}