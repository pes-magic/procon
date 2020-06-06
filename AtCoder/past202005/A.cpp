#include <iostream>
#include <string>

using namespace std;

string solve(const string& s, const string& t){
    if(s == t) return "same";
    if(s.size() == t.size()){
        for(int i=0;i<s.size();i++){
            if(tolower(s[i]) != tolower(t[i])) return "different";
        }
        return "case-insensitive";
    }
    return "different";
}

int main(){
    string s, t;
    cin >> s >> t;
    cout << solve(s, t) << endl;
}