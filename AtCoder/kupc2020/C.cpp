#include <iostream>
#include <vector>
#include <string>

using namespace std;

unsigned int xor32(void) {
    static unsigned int y = 2463534242;
    y = y ^ (y << 13); y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

int main(){
    while(true){
        vector<string> vs(13, string(13, '.'));
        int error = 0;
        vector<vector<int>> ok(26, vector<int>(26, 0));
        for(int i=0;i<13;i++){
            for(int j=0;j<13;j++){
                while(true){
                    if(error > 1000000) break;
                    int t = xor32()%26;
                    if(i-1 >= 0){
                        if(ok[vs[i-1][j]-'a'][t]){ ++error; continue; }
                    }
                    if(j-1 >= 0){
                        if(ok[vs[i][j-1]-'a'][t]){ ++error; continue; }
                    }
                    vs[i][j] = 'a'+t;
                    if(i-1 >= 0){
                        ok[vs[i-1][j]-'a'][t] = 1;
                    }
                    if(j-1 >= 0){
                        ok[vs[i][j-1]-'a'][t] = 1;
                    }
                    break;
                }
            }
        }
        if(error <= 1000000){
            cout << 13 << endl;
            for(auto& s : vs) cout << s << endl;
            break;
        }
    }
}