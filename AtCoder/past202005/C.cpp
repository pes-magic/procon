#include <iostream>

using namespace std;

int main(){
    long long A, R, N; cin >> A >> R >> N;
    if(R == 1) cout << A << endl;
    else {
        for(int i=1;i<N;i++){
            if(A > 1000000000) break;
            A *= R;
        }
        if(A <= 1000000000) cout << A << endl;
        else cout << "large" << endl;
    }
}