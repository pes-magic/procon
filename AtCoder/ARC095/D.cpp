#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    while(cin >> n){
        vector<int> a(n);
        for(auto& t : a) cin >> t;
        sort(a.begin(), a.end());
        int best = a[0];
        int score = min(a[0], a.back() - a[0]);
        for(int i=1;i<n-1;i++){
            int cur = min(a[i], a.back() - a[i]);
            if(cur > score){
                best = a[i];
                score = cur;
            }
        }
        cout << a.back() << " " << best << endl;
    }
}