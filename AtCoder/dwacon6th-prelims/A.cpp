#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        map<string, int> idx;
        vector<int> t(N);
        for(int i=0;i<N;i++){
            string s; cin >> s >> t[i];
            idx[s] = i;
        }
        string name; cin >> name;
        int res = 0;
        for(int i=idx[name]+1;i<N;i++) res += t[i];
        cout << res << endl;
    }
}