#include <iostream>
#include <vector>

using namespace std;



int main(){
    int N, M;
    while(cin >> N >> M){
        string res(N, '?');
        bool valid = true;
        for(int i=0;i<M;i++){
            int s, c; cin >> s >> c;
            if(s == 1 && c == 0 && N != 1) valid = false;
            if(res[s-1] != '?' && res[s-1] - '0' != c) valid = false;
            res[s-1] = c + '0';
        }
        if(valid){
            for(int i=0;i<N;i++){
                if(res[i] == '?') res[i] = (i==0 && N > 1 ? '1' : '0');
            }
            cout << res << endl;
        } else {
            cout << -1 << endl;
        }
    }
}