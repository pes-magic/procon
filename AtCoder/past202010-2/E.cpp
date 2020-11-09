#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string solve(const string& S){
    string T = S;
    sort(T.begin(), T.end());
    do {
        string U = T;
        reverse(U.begin(), U.end());
        if(T != S && U != S) return T;
    } while(next_permutation(T.begin(), T.end()));
    return "None";
}

int main(){
    int N; cin >> N;
    string S; cin >> S;
    cout << solve(S) << endl;
}