#include <iostream>

using namespace std;

int solve(int A, int B){
    for(int i=1;i<=20*B;i++){
        int a = int(0.08*i);
        int b = int(0.1*i);
        if(a == A && b == B) return i;
    }
    return -1;
}

int main(){
    int A, B;
    while(cin >> A >> B){
        cout << solve(A, B) << endl;
    }
}