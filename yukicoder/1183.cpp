#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N), B(N);
        for(auto& t : A) cin >> t;
        for(auto& t : B) cin >> t;
        int res = 0;
        A.push_back(0);
        B.push_back(0);
        for(int i=1;i<=N;i++){
            if(A[i-1] != B[i-1] && A[i] == B[i]) ++res;
        }
        cout << res << endl;
    }
}