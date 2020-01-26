#include <iostream>

using namespace std;

int main(){
    int H, A;
    while(cin >> H >> A){
        cout << (H+A-1)/A << endl;
    }
}