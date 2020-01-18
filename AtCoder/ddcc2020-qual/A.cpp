#include <iostream>

using namespace std;

int main(){
    int a, b;
    while(cin >> a >> b){
        int c[] = {0, 300000, 200000, 100000};
        int res = 0;
        if(a <= 3) res += c[a];
        if(b <= 3) res += c[b];
        if(a+b == 2) res += 400000;
        cout << res << endl;
    }
}