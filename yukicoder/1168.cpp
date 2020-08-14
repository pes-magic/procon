#include <iostream>

using namespace std;

int f(int d){
    int res = 0;
    while(d){
        res += d%10;
        d /= 10;
    }
    return res;
}

int main(){
    int N; cin >> N;
    for(int i=0;i<99;i++) N = f(N);
    cout << N << endl;
}