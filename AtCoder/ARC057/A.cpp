#include <iostream>

using namespace std;

int main(){
    long long A, K;
    while(cin >> A >> K){
        const long long goal = 2000000000000LL;
        if(K == 0){
            cout << max(0LL, goal-A) << endl;
        } else {
            for(int i=0;;i++){
                if(A >= goal){ cout << i << endl; break; }
                A += 1+K*A;
            }
        }
    }
}