#include <iostream>
#include <atcoder/math>

using namespace std;

int main(){
    int T; cin >> T;
    for(int i=0;i<T;i++){
        int n, m, a, b; cin >> n >> m >> a >> b;
        cout << atcoder::floor_sum(n, m, a, b) << endl;
    }
}