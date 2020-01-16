#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        long long s = 0;
        map<long long, int> mp;
        mp[0] = 1;
        for(int i=0;i<N;i++){
            int A; cin >> A;
            s += A;
            if(!mp.count(s)) mp[s] = 0;
            ++mp[s];
        }
        long long res = 0;
        for(auto& t : mp){
            res += t.second * (t.second - 1LL) / 2;
        }
        cout << res << endl;
    }
}