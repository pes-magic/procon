#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<pair<long long, long long>> vp;
        for(int i=0;i<N;i++){
            long long X, L; cin >> X >> L;
            vp.emplace_back(X+L, X-L);
        }
        sort(vp.begin(), vp.end());
        int res = 0;
        long long last = -(1LL << 60);
        for(auto& p : vp){
            if(p.second < last) continue;
            ++res;
            last = p.first;
        }
        cout << res << endl;
    }
}
