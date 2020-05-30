#include <iostream>

using namespace std;

int main(){
    int H1, M1, H2, M2, K; cin >> H1 >> M1 >> H2 >> M2 >> K;
    int a = 60*H1 + M1;
    int b = 60*H2 + M2;
    cout << (b-a-K) << endl;
}