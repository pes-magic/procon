#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int N; cin >> N;
    map<long long, long long> mp;
    mp[0] = 1;
    long long sum = 0;
    long long res = 0;
    for(int i=0;i<N;i++){
        long long a; cin >> a;
        sum += a;
        if(mp.count(sum)){
            res += mp[sum];
            mp[sum]++;
        } else {
            mp[sum] = 1;
        }
    }
    cout << res << endl;
}