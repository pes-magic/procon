#include <iostream>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    if(M == 0){
        for(int i=0;i<N;i++) cout << 2*i+1 << " " << 2*i+2 << endl;
        return 0;
    }
    int a = M+1;
    int b = 1;
    if(M < 0 || N < a+b){
        cout << -1 << endl;
        return 0;
    }
    cout << 1 << " " << 2*a+2 << endl;
    for(int i=0;i<a;i++){
        cout << 2*i+2 << " " << 2*i+3 << endl;
    }
    for(int i=a+b;i<N;i++) cout << 2*i+2*a+3 << " " << 2*i+2*a+4 << endl;
}