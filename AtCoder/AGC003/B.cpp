#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        long long res = 0;
        int prev = 0;
        for(int i=0;i<N;i++){
            int A; cin >> A;
            res += (A+prev)/2;
            prev = (A > 0 ? (A+prev)%2 : 0);
        }
        cout << res << endl;
    }
}