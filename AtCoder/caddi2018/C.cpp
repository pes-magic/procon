#include <iostream>

using namespace std;

int main(){
    long long N, P;
    while(cin >> N >> P){
        long long res = 1;
        for(long long d=2;d*d<=P;d++){
            if(P%d) continue;
            int cnt = 0;
            while(P%d == 0){
                ++cnt;
                P /= d;
            }
            for(int i=0;i<cnt/N;i++) res *= d;
        }
        if(P > 1 && N == 1) res *= P;
        cout << res << endl;
    }
}