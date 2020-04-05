#include <iostream>
#include <vector>
#include <string>

using namespace std;

int read(int pos){
    cout << pos+1 << endl;
    int res; cin >> res;
    return res;
}

bool solve(int B){
    string res(B, '?');
    vector<int> same(B, 0);
    int idxS = 0, idxD = 0;
    int check = 0;
    for(int i=0;i<15;i++){
        int s = read(idxS);
        int d = read(idxD);
        bool revS = (res[idxS] - '0' != s);
        bool revD = (res[idxD] - '0' != d);
        for(int j=0;j<B;j++){
            if(res[j] == '?') continue;
            if(same[j] ? revS : revD) res[j] = (res[j] == '0' ? '1' : '0');
        }
        for(int j=0;j<4;j++){
            if(check < B/2){
                res[check] = read(check) + '0';
                int checkR = B-1-check;
                res[checkR] = read(checkR) + '0';
                if(res[check] == res[checkR]){
                    same[check] = same[checkR] = 1;
                    idxS = check;
                } else {
                    idxD = check;
                }
                ++check;
            } else {
                read(0);
                read(0);
            }
        }
    }
    cout << res << endl;
    char c; cin >> c;
    return c == 'Y';
}

int main(){
    int T, B; cin >> T >> B;
    for(int i=0;i<T;i++) if(!solve(B)) break;
}