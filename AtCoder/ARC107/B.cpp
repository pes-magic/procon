#include <iostream>

using namespace std;

int main(){
    int N, K; cin >> N >> K;
    long long res = 0;
    auto cnt = [&](int sum){
        int all = sum-1;
        int s = max(0, sum-1-N);
        return (long long)all-2*s;
    };
    for(int i=2;i<=2*N;i++){
        int dst = i+K;
        if(dst < 2 || 2*N < dst) continue;
        res += cnt(i) * cnt(dst);
    }
    cout << res << endl;
}