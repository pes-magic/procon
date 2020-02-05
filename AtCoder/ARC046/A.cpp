#include <iostream>
#include <string>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        cout << string((N+8)/9, (N-1)%9+'1') << endl;
    }
}