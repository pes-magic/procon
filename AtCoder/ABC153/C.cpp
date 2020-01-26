#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<int> H(N);
        for(auto& t : H) cin >> t;
        sort(H.begin(), H.end());
        long long res = 0;
        for(int i=0;i<N-K;i++) res += H[i];
        cout << res << endl;
    }
}