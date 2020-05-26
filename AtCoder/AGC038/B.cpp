#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
    int N, K; cin >> N >> K;
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    set<int> S;
    int prev = 100;
    int cnt = 0;
    int sr = 0;
    int res = 0;
    for(int i=0;i<N;i++){
        if(prev > a[i]) cnt = 1;
        else ++cnt;
        prev = a[i];
        if(cnt >= K) sr = 1;
        else if(i >= K-1) ++res;
        S.insert(a[i]);
        if(i >= K){
            if(cnt < K && *S.rbegin() == a[i] && *S.begin() == a[i-K]) --res;
            S.erase(a[i-K]);
        }
    }
    cout << res + sr << endl;
}
