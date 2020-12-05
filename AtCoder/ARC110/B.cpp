#include <iostream>
#include <string>

using namespace std;

const long long r = 10000000000;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    const string T = "110";
    if(S == "0"){
        cout << r << endl;
    } else if(S == "1"){
        cout << 2*r << endl;
    } else {
        for(int i=0;i<3;i++){
            bool ok = true;
            for(int j=0;j<N;j++){
                if(S[j] != T[(i+j)%3]) ok = false;
            }
            if(!ok) continue;
            cout << r - (N+i-1)/3 << endl;
            return 0;
        }
        cout << 0 << endl;
    }
}