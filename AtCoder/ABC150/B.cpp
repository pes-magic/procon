#include <iostream>
#include <string>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        string S; cin >> S;
        int pos = -1;
        int res = 0;
        while(true){
            pos = S.find("ABC", pos+1);
            if(pos == string::npos) break;
            ++res;
        }
        cout << res << endl;
    }
}