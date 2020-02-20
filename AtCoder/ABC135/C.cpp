#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N+1), B(N);
        for(auto& t : A) cin >> t;
        for(auto& t : B) cin >> t;
        long long res = 0;
        for(int i=N-1;i>=0;i--){
            for(int j=1;j>=0;j--){
                int d = min(A[i+j], B[i]);
                res += d;
                A[i+j] -= d;
                B[i] -= d;
            }
        }
        cout << res << endl;
    }
}