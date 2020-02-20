#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        int cnt = 0;
        for(int i=1;i<=N;i++){
            int t; cin >> t;
            if(t != i) ++cnt;
        }
        cout << (cnt <= 2 ? "YES" : "NO") << endl;
    }
}