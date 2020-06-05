#include <iostream>

using namespace std;

int main(){
    int N, D1, D2; cin >> N >> D1 >> D2;
    int v1 = 1, v2 = 1;
    while(D1%4 == 0){ D1 /= 4; v1 *= 2; }
    while(D2%4 == 0){ D2 /= 4; v2 *= 2; }
    int cnt = 0;
    for(int i=0;i<2*N;i++){
        for(int j=0;j<2*N;j++){
            if(D1%2 == 1){
                if((i/v1 + j/v1)%2 == 1) continue;
            } else {
                if(i/v1%2 == 1) continue;
            }
            if(D2%2 == 1){
                if((i/v2 + j/v2)%2 == 1) continue;
            } else {
                if(i/v2%2 == 1) continue;
            }
            if(cnt < N*N) cout << i << " " << j << endl;
            ++cnt;
        }
    }
}