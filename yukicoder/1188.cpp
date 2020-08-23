#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> LIS(const vector<int>& v){
    vector<int> res(v.size(), 1);
    vector<int> a(v.size(), v[0]);
    auto end = a.begin();
    ++end;
    for(int i=1;i<v.size();i++){
        auto l = lower_bound(a.begin(), end, v[i]);
        if(l == end) ++end;
        *l = v[i];
        res[i] = distance(a.begin(), l) + 1;
    }
    return res;
}

int solve(vector<int>& a){
    auto f = LIS(a);
    reverse(a.begin(), a.end());
    auto g = LIS(a);
    int res = 0;
    for(int i=0;i<a.size();i++){
        res = max(res, min(f[i], g[a.size()-i-1])-1);
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N), B(N);
        for(int i=0;i<N;i++){
            cin >> A[i];
            B[i] = -A[i];
        }
        cout << max(solve(A), solve(B)) << endl;
    }
}