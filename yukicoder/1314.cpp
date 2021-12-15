#include <iostream>

using namespace std;

int main(){
    int M, K; cin >> M >> K;
    int lose = (M-1)/(K+1);
    int win = M-lose-1;
    int a = (win+1)/2;
    int b = win/2;
    if(a==b) b += lose;
    else a += lose;
    if(a > b) cout << "Win" << endl;
    else if(a < b) cout << "Lose" << endl;
    else cout << "Draw" << endl;
}