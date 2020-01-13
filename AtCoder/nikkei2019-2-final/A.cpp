#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        long long res = 0;
        for(int i=0;i<N;i++){
            int a = 0, b = 0;
            for(int j=0;j<i;j++) if(A[j] < A[i]) ++a;
            for(int j=i+1;j<N;j++) if(A[j] < A[i]) ++b;
            res += a * b;
        }
        cout << res << endl;
    }
}