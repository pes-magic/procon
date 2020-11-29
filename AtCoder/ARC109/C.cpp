#include <iostream>
#include <string>

using namespace std;

char battle(char a, char b){
    if(a=='R'){
        if(b == 'P') return 'P';
        else return 'R';
    }
    if(a=='S'){
        if(b=='R') return 'R';
        else return 'S';
    }
    if(a=='P'){
        if(b=='S') return 'S';
        else return 'P';
    }
}

string next(const string& S){
    auto T = S;
    if(S.size()%2) T += S;
    string res = "";
    for(int i=0;i<T.size();i+=2){
        res += battle(T[i], T[i+1]);
    }
    return res;
}

int main(){
    int n, k; cin >> n >> k;
    string S; cin >> S;
    for(int i=0;i<k;i++) S = next(S);
    cout << (char)S[0] << endl;
}