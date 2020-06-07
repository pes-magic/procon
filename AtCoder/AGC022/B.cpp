#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    if(N==3){
        cout << 2 << " " << 5 << " " << 63 << endl;
        return 0;
    }
    int a[8][8] = {
        {6},
        {2, 4},
        {2, 4, 6},
        {2, 3, 4, 9},
        {2, 3, 4, 6, 9},
        {2, 3, 4, 6, 9, 12},
        {2, 3, 4, 6, 8, 9, 10},
        {2, 3, 4, 6, 8, 9, 10, 12}
    };

    for(int i=0;i<30000;i+=12){
        int p = min(N, 8);
        for(int j=0;j<p;j++) cout << i + a[p-1][j] << " ";
        N -= 8;
        if(N <= 0) break;
    }
    cout << endl;
}