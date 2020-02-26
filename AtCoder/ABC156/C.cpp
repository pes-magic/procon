#include <iostream>
#include <vector>

using namespace std;

long long calc(const vector<int>& X, int P){
    long long res = 0;
    for(auto& t : X) res += (P-t)*(P-t);
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> X(N);
        for(auto& t : X) cin >> t;
        long long res = (1LL << 60);
        for(int i=0;i<=100;i++) res = min(res, calc(X, i));
        cout << res << endl;
    }
}