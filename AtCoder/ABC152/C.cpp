#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        int best = N+1;
        int res = 0;
        for(int i=0;i<N;i++){
            int A; cin >> A;
            if(best > A){
                ++res;
                best = A;
            }
        }
        cout << res << endl;
    }
}