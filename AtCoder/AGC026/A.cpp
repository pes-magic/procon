#include <iostream>

using namespace std;

int main(){
    int N; cin >> N;
    int res = 0;
    int cnt = 0;
    int prev = -1;
    for(int i=0;i<N;i++){
        int a; cin >> a;
        if(a != prev){
            res += cnt/2;
            cnt = 1;
        } else {
            ++cnt;
        }
        prev = a;
    }
    res += cnt/2;
    cout << res << endl;
}