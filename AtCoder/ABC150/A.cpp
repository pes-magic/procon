#include <iostream>

using namespace std;

int main(){
    int K, X;
    while(cin >> K >> X){
        cout << (500*K >= X ? "Yes" : "No") << endl;
    }
}