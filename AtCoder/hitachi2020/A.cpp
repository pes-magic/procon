#include <iostream>
#include <string>

using namespace std;

bool solve(const string& s){
    if(s.size()%2) return false;
    for(int i=0;i<s.size();i++){
        if(s[i] != "hi"[i%2]) return false;
    }
    return true;
}

int main(){
    string S;
    while(cin >> S){
        cout << (solve(S) ? "Yes" : "No") << endl;
    }
}