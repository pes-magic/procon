#include <iostream>

using namespace std;

int main(){
    int M;
    while(cin >> M){
        long long res = 0;
        long long sum = 0;
        for(int i=0;i<M;i++){
            long long d, c; cin >> d >> c;
            res += c;
            sum += d*c;
        }
        --res;
        res += (sum-1)/9;
        cout << res << endl;
    }
}