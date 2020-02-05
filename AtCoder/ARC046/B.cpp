#include <iostream>

using namespace std;

int main(){
    int N, A, B;
    while(cin >> N >> A >> B){
        if(A > B){
            cout << "Takahashi" << endl;
        } else if(A < B){
            cout << (N <= A ? "Takahashi" : "Aoki") << endl;
        } else {
            cout << (N%(A+1) ? "Takahashi" : "Aoki") << endl;
        }
    }
}