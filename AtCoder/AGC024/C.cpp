#include <iostream>
#include <vector>

using namespace std;

long long solve(vector<int>& A){
    if(A[0]) return -1;
    long long res = 0;
    int pre = 0;
    for(auto& t : A){
        if(t >= pre + 2) return -1;
        res += (t == pre+1 ? 1 : t);
        pre = t;
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        cout << solve(A) << endl;
    }
}