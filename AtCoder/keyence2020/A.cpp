#include <iostream>

using namespace std;

int main(){
    int W, H, N;
    while(cin >> W >> H >> N){
        int m = max(W, H);
        cout << (N+m-1)/m << endl;
    }
}