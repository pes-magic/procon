#include <iostream>
#include <string>

using namespace std;

int main(){
    string S;
    while(cin >> S){
        int res = 0;
        string pre = "";
        for(int i=0;i<S.size();i++){
            if(pre.size() == 1 && pre[0] == S[i]){
                if(i+1 < S.size()){
                    pre = S.substr(i, 2);
                    ++res;
                    ++i;
                }
            } else {
                pre = S[i];
                ++res;
            }
        }
        cout << res << endl;
    }
}