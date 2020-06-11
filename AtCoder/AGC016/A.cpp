#include <iostream>
#include <string>

using namespace std;

int main(){
    string S; cin >> S;
    int res = S.size();
    for(int i=0;i<26;i++){
        int m = 0;
        int c = 0;
        for(auto& s : S){
            if(s == 'a' + i){
                m = max(m, c);
                c = 0;
            } else {
                ++c;
            }
        }
        res = min(res, max(m, c));
    }
    cout << res << endl;
}