#include <iostream>

using namespace std;

int main(){
    long long N, M;
    while(cin >> N >> M){
        if(N > M) swap(N, M);
        cout << abs((N-2)*(M-2)) << endl;
    }
}