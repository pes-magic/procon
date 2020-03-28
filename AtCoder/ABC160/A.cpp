#include <iostream>
#include <string>

using namespace std;

int main(){
    string S;
    while(cin >> S){
        cout << (S[2]==S[3] && S[4]==S[5] ? "Yes" : "No") << endl;
    }
}