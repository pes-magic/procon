#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        int res = 0;
        for(int i=10;i<100;i++) if(i <= N && i%3 == 0) ++res;
        for(int i=0;i<(1<<20);i++){
            long long c = i, v = 0;
            for(int j=0;j<10;j++){
                v = 10 * v + c%4 * 3;
                c /= 4;
            }
            if(100 <= v && v <= N) ++res;
        }
        cout << res << endl;
    }
}