#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;


void solve(int N){
    for(int i=1;i<N;i++){
        cout << "M " << i << " " << N << endl;
        int p; cin >> p;
        if(p != i){
            cout << "S " << i << " " << p << endl;
            cin >> p;
        }
    }
    cout << "D" << endl;
    int p; cin >> p;
}

int main(){
    int T, N; cin >> T >> N;
    for(int t=1;t<=T;t++){
        solve(N);
    }
}