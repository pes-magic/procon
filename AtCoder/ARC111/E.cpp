#include <iostream>
#include <atcoder/math>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t=0;t<T;t++){
        long long A, B, C, D; cin >> A >> B >> C >> D;
        auto N = (D+C-B-2)/(C-B);
        auto res = atcoder::floor_sum(N, D, C, A) - atcoder::floor_sum(N, D, B, A-1);
        cout << (N-1-res) << endl;
    }
}