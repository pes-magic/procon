#include <iostream>
#include <vector>
#include <numeric>
#include <cstdio>

using namespace std;

bool check(const vector<int>& v, int A, int B, int M){
    vector<int> cur(max<int>(M+1, v.size()), 0);
    cur[M] = 1;
    for(int i=cur.size()-1;i>0;i--){
        if(i < v.size()){
            if(v[i] > cur[i]) return false;
            cur[i] -= v[i];
        }
        if(i-A > 0) cur[i-A] += cur[i];
        if(i-B > 0) cur[i-B] += cur[i];
    }
    return true;
}

int solve(const vector<int>& v, int A, int B){
    int d = gcd(A, B);
    int m = -1;
    for(int i=1;i<v.size();i++){
        if(v[i] == 0) continue;
        if(m == -1) m = i%d;
        if(i%d != m) return -1;
    }
    for(int i=1;;i++) if(check(v, A, B, i)) return i;
}

int main(){

    int T; cin >> T;
    for(int i=1;i<=T;i++){
        int N, A, B; cin >> N >> A >> B;
        vector<int> v(N+1, 0);
        for(int i=1;i<=N;i++) cin >> v[i];
        int res = solve(v, A, B);
        printf("Case #%d: ", i);
        if(res == -1){
            printf("IMPOSSIBLE\n");
        } else {
            printf("%d\n", res);
        }
    }
}
