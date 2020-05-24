#include <iostream>

using namespace std;

int main(){
    long long N, A, B; cin >> N >> A >> B;
    if((B-A)%2 == 0){
        cout << (B-A)/2 << endl;
    } else {
        cout << min(A-1, N-B)+(B-A+1)/2 << endl;
    }
}