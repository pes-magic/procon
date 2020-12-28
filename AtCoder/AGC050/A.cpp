#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    for(int i=0;i<N;i++){
        cout << (2*i+1)%N+1 << " " << (2*i+2)%N+1 << endl;
    }
}