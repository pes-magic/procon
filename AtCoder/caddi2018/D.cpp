#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        bool win = false;
        for(int i=0;i<N;i++){
            int a; cin >> a;
            if(a%2) win = true;
        }
        cout << (win ? "first" : "second") << endl;
    }
}