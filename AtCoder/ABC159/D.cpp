#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        vector<long long> num(N+1, 0);
        for(int i=0;i<N;i++){
            cin >> A[i];
            num[A[i]]++;
        }
        long long res = 0;
        for(auto& t : num) res += t*(t-1)/2;
        for(auto& t : A){
            auto v = num[t];
            if(v <= 1){
                cout << res << endl;
            } else {
                cout << res - v*(v-1)/2 + (v-1)*(v-2)/2 << endl;
            }
        }
    }
}