#include <iostream>
#include <string>

using namespace std;

int main(){
    int a, b;
    while(cin >> a >> b){
        string s(a, '0'+b), t(b, '0'+a);
        cout << min(s, t) << endl;
    }
}