#include <iostream>
#include <vector>

using namespace std;

bool enable(long long mask, int src, int dst){
    if(dst > src) return false;
    vector<int> dp(src+1, 0);
    dp[src] = 1;
    for(int i=49;i>=0;i--){
        if(!(mask&(1LL<<i))) continue;
        for(int j=0;j<=src;j++){
            if(!dp[j]) continue;
            dp[j%(i+1)] = 1;
        }
    }
    return dp[dst];
}

bool check(long long mask, const vector<int>& a, const vector<int>& b){
    for(int i=0;i<a.size();i++) if(!enable(mask, a[i], b[i])) return false;
    return true;
}

int main(){
    int N; cin >> N;
    vector<int> a(N), b(N);
    for(auto& t : a) cin >> t;
    for(auto& t : b) cin >> t;
    long long all = (1LL<<50)-1;
    if(!check(all, a, b)){
        cout << -1 << endl;
        return 0;
    }
    for(int i=49;i>=0;i--){
        all ^= (1LL << i);
        if(!check(all, a, b)) all |= (1LL << i);
    }
    cout << 2*all << endl;
}