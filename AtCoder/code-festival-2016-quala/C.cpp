#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    while(cin >> s){
        int K; cin >> K;
        for(auto& c : s){
            if(c == 'a') continue;
            int sub = 26 - (c-'a');
            if(sub <= K){
                c = 'a';
                K -= sub;
            }
        }
        s.back() = (s.back()-'a'+K)%26 + 'a';
        cout << s << endl;
    }
}