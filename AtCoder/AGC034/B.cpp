#include <iostream>
#include <string>

using namespace std;

int main(){
    string s; cin >> s;
    int cntA = 0;
    long long res = 0;
    for(int i=0;i<s.size();i++){
        if(s[i] == 'A'){
            ++cntA;
        } else if(s[i] == 'B'){
            if(i+1 < s.size() && s[i+1] == 'C'){
                res += cntA;
                ++i;
            } else {
                cntA = 0;
            }
        } else {
            cntA = 0;
        }
    }
    cout << res << endl;
}