#include <iostream>
#include <map>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t=0;t<T;t++){
        int N; cin >> N;
        map<int, int> mp;
        for(int i=0;i<N;i++){
            int a; cin >> a;
            if(!mp.count(a)) mp[a] = 1;
            else ++mp[a];
        }
        if(N%2 == 1){
            cout << "Second" << endl;
        } else {
            bool win = false;
            for(auto& p : mp) if(p.second%2 == 1) win = true;
            cout << (win ? "First" : "Second") << endl;
        }
    }
}