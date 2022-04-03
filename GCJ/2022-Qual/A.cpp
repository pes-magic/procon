#include <iostream>

using namespace std;

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        int R, C; cin >> R >> C;
        cout << "Case #" << i << ":" << endl;
        cout << "..+";
        for(int j=1;j<C;j++) cout << "-+";
        cout << endl;
        for(int j=0;j<R;j++){
            cout << (j==0 ? "." : "|");
            for(int k=0;k<C;k++) cout << ".|";
            cout << endl;
            cout << "+";
            for(int k=0;k<C;k++) cout << "-+";
            cout << endl;
        }
    }
}