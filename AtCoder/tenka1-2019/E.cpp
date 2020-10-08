#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> a(N);
    for(int i=N-1;i>=0;i--) cin >> a[i];
    int b; cin >> b;
    vector<int> prime(N+1, 1);
    vector<int> res;
    for(int d=2;d<=N;d++){
        if(!prime[d]) continue;
        for(int j=2*d;j<=N;j+=d) prime[j] = 0;
        if(abs(b)%d != 0) continue;
        vector<long long> sum(d-1, 0);
        for(int i=0;i<N;i++) sum[i%(d-1)] += a[i];
        bool ok = true;
        for(auto& t : sum) if(t%d != 0) ok = false;
        if(ok) res.push_back(d);
    }
    int s = abs(N ? a.back() : b);
    if(b) s = std::gcd(s, abs(b));
    for(auto& t : a) if(t) s = std::gcd(s, abs(t));
    for(int i=2;i*i<=s;i++){
        if(s%i != 0) continue;
        if(i > N) res.push_back(i);
        while(s%i == 0) s /= i;
    }
    if(s > 1 && s > N) res.push_back(s);
    for(auto& t : res) cout << t << endl;
}