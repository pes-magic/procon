#include <iostream>

using namespace std;

int main(){
    int A, B;
    while(cin >> A >> B){
        if((A+B)%2){
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << (A+B)/2 << endl;
        }
    }
}