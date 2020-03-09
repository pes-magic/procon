#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> solve(const vector<long long>& a){
    const int N = a.size();
    vector<long long> res(N+1, 0);
    bool zero = false;
    if(a.back() < 0) res[N-1] = 1;
    else if(a.back() == 0) zero = true;
    vector<pair<int, int>> mergin;
    for(int i=N-2;i>=0;i--){
        auto cur = a[i], next = a[i+1];
        if(zero){
            if(cur != 0){
                for(int j=0;j<=i;j++) res[j] = -1;
                return res;
            } else {
                res[i] = res[i+1];
                continue;
            }
        } else if(cur == 0){
            zero = true;
            res[i] = res[i+1];
            continue;
        }
        res[i] = res[i+1] + (a[i] < 0 ? 1 : 0);
        if(cur < 0) cur *= -2;
        if(next < 0) next *= -2;
        if(cur <= next){
            int m = 0;
            while(4*cur <= next){
                m += 2;
                cur *= 4;
            }
            if(m > 0) mergin.emplace_back(m, i);
        } else {
            int m = 0;
            while(next < cur){
                m += 2;
                next *= 4;
            }
            while(m > 0){
                if(mergin.empty()){
                    res[i] += (N-1-i) * m;
                    break;
                } else {
                    int sub = min(m, mergin.back().first);
                    res[i] += (mergin.back().second-i) * sub;
                    m -= sub;
                    mergin.back().first -= sub;
                    if(!mergin.back().first) mergin.pop_back();
                }
            }
        }
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<long long> a(N);
        for(auto& t : a) cin >> t;
        auto p = solve(a);
        reverse(a.begin(), a.end());
        for(auto& t : a) t *= -1;
        auto n = solve(a);
        long long res = -1;
        for(int i=0;i<=N;i++){
            if(p[i] == -1 || n[N-i] == -1) continue;
            long long cur = p[i] + n[N-i];
            if(res == -1 || cur < res) res = cur;
        }
        cout << res << endl;
    }
}