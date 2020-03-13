#include <iostream>

using namespace std;

int main(){
    long long A, B, C, K;
    while(cin >> A >> B >> C >> K){
        cout << (K%2 ? B-A : A-B) << endl;
    }
}