#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<long long> a(N), b(N);
        for(auto& t : a) cin >> t;
        for(auto& t : b) cin >> t;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        long long L = 0, R = a.back() * b.back();
        while(R - L > 1){
            auto mid = (L+R)/2;
            int n = 0;
            for(auto& t : a){
                n += upper_bound(b.begin(), b.end(), mid/t) - b.begin();
            }
            if(n >= K) R = mid;
            else L = mid;
        }
        cout << R << endl;
    }
}