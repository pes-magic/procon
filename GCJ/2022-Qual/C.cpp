#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        cout << "Case #" << test << ": ";
        int N; cin >> N;
        vector<int> v(N);
        for(auto& t : v) cin >> t;
        sort(v.begin(), v.end());
        int res = 0;
        for(auto& t : v){
            if(res < t) ++res;
        }
        cout << res << endl;
    }
}