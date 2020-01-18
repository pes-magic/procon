#include <iostream>
#include <string>

using namespace std;

bool check(const string& S){
    string T = "keyence";
    if(S.size() < T.size()) return false;
    int a = 0, b = 0;
    for(int i=0;i<T.size();i++){ 
        if(S[i] != T[i]) break;
        a++;
    }
    for(int i=0;i<T.size();i++){
        if(S[S.size()-1-i] != T[T.size()-1-i]) break;
        b++;
    }
    return (a+b >= T.size());
}

int main(){
    string S;
    while(cin >> S){
        cout << (check(S) ? "YES" : "NO") << endl;
    }
}