#include <iostream>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        cout << (N*(N-1)/2 + M*(M-1)/2) << endl;
    }
}