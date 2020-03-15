#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> checkEnable(const string& a, const string& b){
    vector<int> res(a.size()+b.size()+1, 1);
    for(int i=0;i<a.size();i++){
        bool ok = true;
        for(int j=0;j<b.size();j++){
            if(i+j >= a.size()) break;
            if(a[i+j] != '?' && b[j] != '?' && a[i+j] != b[j]) ok = false;
        }
        if(!ok) res[i] = 0;
    }
    return res;
}

int solve(const string& a, const string& b, const string&c, const vector<int>& ab, const vector<int>& ac, const vector<int>& bc){
    int res = a.size() + b.size() + c.size();
    for(int i=0;i<=a.size();i++){
        if(!ab[i]) continue;
        for(int j=i;j<=max<int>(a.size(), i+b.size());j++){
            if(!(ac[j] && bc[j-i])) continue;
            res = min(res, max<int>(a.size(), max<int>(b.size()+i, c.size()+j)));
        }
    }
    return res;
}

int main(){
    string a, b, c;
    while(cin >> a >> b >> c){
        auto ab = checkEnable(a, b);
        auto ac = checkEnable(a, c);
        auto ba = checkEnable(b, a);
        auto bc = checkEnable(b, c);
        auto ca = checkEnable(c, a);
        auto cb = checkEnable(c, b);
        int res = a.size() + b.size() + c.size();
        res = min(res, solve(a, b, c, ab, ac, bc));
        res = min(res, solve(a, c, b, ac, ab, cb));
        res = min(res, solve(b, a, c, ba, bc, ac));
        res = min(res, solve(b, c, a, bc, ba, ca));
        res = min(res, solve(c, a, b, ca, cb, ab));
        res = min(res, solve(c, b, a, cb, ca, ba));
        cout << res << endl;
    }
}