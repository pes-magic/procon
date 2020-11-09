#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    int X, Y; cin >> X >> Y;
    if(Y){
        int S = 100*X/Y;
        printf("%d.%02d\n", S/100, S%100);
    } else {
        cout << "ERROR" << endl;
    }
}
