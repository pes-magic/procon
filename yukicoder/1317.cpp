#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main(){
    map<string, int> mp = {
        {"AC", 0},
        {"WA", 1},
        {"TLE", 2},
        {"MLE", 3},
        {"OLE", 4},
        {"RE", 5}
    };
    int N; cin >> N;
    for(int _=0;_<N;_++){
        vector<int> a(6), b(6);
        for(auto& t : a) cin >> t;
        for(auto& t : b) cin >> t;
        string X; cin >> X;
        bool ok = true;
        if(a[mp[X]] > 0) ok = false;
        for(int i=1;i<b.size();i++) if(i != mp[X] && b[i] > 0) ok = false;
        cout << (ok ? "Yes" : "No") << endl;
    }
}