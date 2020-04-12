#include <iostream>
#include <vector>

using namespace std;

int main(){
    long long N;
    while(cin >> N){
        vector<int> res;
        for(int i=1;(1LL<<i)-1<=N;i++) res.push_back(i);
        N -= (1LL << res.size()) - 1;
        int cur = res.size() + 1;
        for(int i=res.size();i>=0;i--){
            if(N&(1LL<<i)){
                auto it = res.begin();
                for(int j=0;j<i;j++) ++it;
                res.insert(it, cur);
                ++cur;
            }
        }
        for(int i=1;i<cur;i++) res.push_back(i);
        cout << res.size() << endl;
        cout << res[0];
        for(int i=1;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}