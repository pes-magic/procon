#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(const vector<int>& a){
    const int N = a.size();
    int m = *min_element(a.begin(), a.end());
    int M = *max_element(a.begin(), a.end());
    if(M - m > 1) return false;
    if(M == m){
        return M == N-1 || 2*M <= N;
    }
    auto c = count_if(a.begin(), a.end(), [&](int t){ return t == m; });
    return c <= m && c + 2 * (M-c) <= N;
}

int main(){
    int N; cin >> N;
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    cout << (check(a) ? "Yes" : "No") << endl;
}