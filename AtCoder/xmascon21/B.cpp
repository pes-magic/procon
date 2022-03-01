#include <iostream>

using namespace std;

int main(){
    long long N, M;
    cin >> N >> M;
    // N/2, (N-1)/2
    /*
    0 0 0  0
    1 0 0  0
    2 1 0  1
    3 1 1
    4 2 1
    5 2 2
    6
    7
    */
    cout << (N+1)*(M+1)-N*M << " " << (N+1)*(M+1)-N*M + (N/2)*(M/2) + ((N-1)/2)*((M-1)/2) << endl;

}