#include <iostream>

using namespace std;

int main(){
    long long A;
    while(cin >> A){
        long long res = A;
        for(long long i=2;;i++){
            if(i >= res) break;
            int c = 0;
            long long cur = A;
            while(cur > 1){
                c++;
                cur = (cur+i-1)/i;
            }
            res = min(res, c*i);
        }
        cout << res << endl;
    }
}