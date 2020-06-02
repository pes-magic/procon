#include <iostream>
#include <vector>

using namespace std;

long long solve(const vector<long long>& X, int L){
    const int N = X.size();
    if(N == 1) return X[0];
    int addIdx = 0;
    int addMul = N;
    int subIdx = N-1;
    int subMul = N-1;
    long long cur = 0;
    while(addMul > 0){
        cur += min(2, addMul) * X[addIdx];
        ++addIdx;
        addMul -= 2;
    }
    --addIdx;
    while(subMul > 0){
        cur += min(2, subMul) * (L - X[subIdx]);
        --subIdx;
        subMul -= 2;
    }
    ++subIdx;
    long long res = cur;
    for(int i=0;i<N-1;i++){
        if(addMul == 0){
            ++addIdx;
            addMul = -1;
        } else {
            addMul = 0;
        }
        cur += X[addIdx];
        cur -= 2 * X[i];
        cur -= L - X[subIdx];
        if(subMul == -1){
            ++subIdx;
            subMul = 0;
        } else {
            subMul = -1;
        }
        res = max(cur, res);
    }
    return res;
}

int main(){
    long long L, N; cin >> L >> N;
    vector<long long> X(N), Y(N);
    for(auto& x : X) cin >> x;
    for(int i=0;i<N;i++) Y[i] = L - X[N-1-i];
    cout << max(solve(X, L), solve(Y, L)) << endl;
}