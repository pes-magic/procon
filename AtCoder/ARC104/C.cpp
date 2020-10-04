#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> p(2*N, -1);
    vector<int> a(2*N, 0);
    vector<int> b(2*N, 0);
    vector<int> see(2*N, 0);
    bool valid = true;
    for(int i=0;i<N;i++){
        int A, B; cin >> A >> B;
        if(A != -1){
            if(see[A-1]) valid = false;
            see[A-1] = 1;
        }
        if(B != -1){
            if(see[B-1]) valid = false;
            see[B-1] = 1;
        }
        if(A != -1 && B != -1) p[A-1] = B-1;
        if(A != -1 && B == -1) a[A-1] = 1;
        if(A == -1 && B != -1) b[B-1] = 1;
    }
    if(!valid){
        cout << "No" << endl;
        return 0;
    }
    vector<int> dp(N+1, 0);
    dp[0] = 1;
    for(int i=0;i<N;i++){
        if(!dp[i]) continue;
        for(int j=1;i+j<=N;j++){
            bool check = true;
            for(int k=0;k<j;k++){
                int f = 2*i+k;
                int s = 2*i+j+k;
                if(p[f] != -1 && p[f] != s) check = false;
                if(a[s] || b[f]) check = false;
                if(a[f] && b[s]) check = false;
            }
            if(check) dp[i+j] = 1;
        }
    }
    cout << (dp.back() ? "Yes" : "No") << endl;
}