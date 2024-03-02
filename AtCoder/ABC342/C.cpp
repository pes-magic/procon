#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    vector<int> rep(26, 0);
    for(int i=0;i<26;i++) rep[i] = i;
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++){
        char s, t; cin >> s >> t;
        for(int i=0;i<26;i++){
            if(rep[i] == s-'a') rep[i] = t-'a';
        }
    }
    for(char c : S) cout << (char)('a' + rep[c-'a']);
    cout << endl;
}