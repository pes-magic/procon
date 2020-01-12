#include <iostream>

using namespace std;

int main(){
    int N, K, M;
    while(cin >> N >> K >> M){
        int res = N*M;
        for(int i=0;i<N-1;i++){
            int A; cin >> A;
            res -= A;
        }
        cout << (res > K ? -1 : max(0, res)) << endl;
    }
}