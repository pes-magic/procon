#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> d(N);
        for(auto& t : d) cin >> t;
        auto sum = accumulate(d.begin(), d.end(), 0);
        auto m = *max_element(d.begin(), d.end());
        cout << sum << endl;
        cout << max(0, 2*m-sum) << endl;
    }
}