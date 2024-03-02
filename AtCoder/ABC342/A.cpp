#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string S; cin >> S;
    vector<int> cnt(26, 0);
    for(char c : S) cnt[c-'a']++;
    for(int i = 0; i < 26; i++){
        if(cnt[i] == 1){
            cout << S.find((char)('a' + i)) + 1 << endl;
        }
    }
}