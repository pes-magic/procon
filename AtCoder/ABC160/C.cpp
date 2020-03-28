#include <iostream>
#include <vector>

using namespace std;

int main(){
    int K, N;
    while(cin >> K >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        int res = 0;
        for(int i=0;i+1<N;i++) res = max(res, A[i+1] - A[i]);
        res = max(res, K-A.back()+A[0]);
        cout << (K-res) << endl;
    }
}