#include <iostream>
#include <vector>
#include <atcoder/convolution>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<long long> a(N);
    vector<long long> b(M);
    for(auto& t : a) cin >> t;
    for(auto& t : b) cin >> t;
    auto c = atcoder::convolution(a, b);
    for(int i=0;i<N+M-1;i++) cout << c[i] << " ";
    cout << endl;
}