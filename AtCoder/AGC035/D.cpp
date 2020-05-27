#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<pair<int, int>, long long> mp[18][18];

long long solve(const vector<long long>& A, int src, int dst, int m1, int m2){
    if(dst < src) return 0;
    if(mp[src][dst].count(make_pair(m1, m2))) return mp[src][dst][make_pair(m1, m2)];
    long long res = (1LL << 60);
    for(int i=src;i<=dst;i++){
        res = min(res, (m1+m2)*A[i] + solve(A, src, i-1, m1, m1+m2) + solve(A, i+1, dst, m1+m2, m2));
    }
    return mp[src][dst][make_pair(m1, m2)] = res;
}

long long solve(const vector<long long>& A){
    return A.front() + A.back() + solve(A, 1, A.size()-2, 1, 1);
}

int main(){
    int N; cin >> N;
    vector<long long> A(N);
    for(auto& t : A) cin >> t;
    cout << solve(A) << endl;
}