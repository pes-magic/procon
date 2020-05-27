#include <iostream>

using namespace std;

int main(){
    long long m = 1000000000;
    long long S; cin >> S;
    if(S == m * m){
        cout << "0 0 0 " << m << " " << m << " " << m << endl;
    } else if(S <= m){
        cout << "0 0 0 " << S << " 1 " << S << endl;
    } else {
        cout << "1 0 0 " << m << " " << 1+S/m << " " << S%m << endl;
    }
}