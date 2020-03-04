#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solve(int N, int A, int B){
    vector<int> res(N), used(N+1, 0);
    for(int dec=1;;dec++){
        int start = max(1, N-dec*A+1);
        for(int i=0;i<A;i++){
            int idx = (dec-1)*A+i;
            if(idx >= N) return vector<int>();
            if(dec > 1 && dec-1+N-idx == B){
                int v = N;
                for(int j=idx;j<N;j++){
                    while(used[v]) --v;
                    res[j] = v--;
                }
                return res;
            }
            res[idx] = start + i;
            used[start+i] = 1;
        }
        if(A == N && B == 1) return res;
    }
    return vector<int>();
}

int main(){
    int N, A, B;
    while(cin >> N >> A >> B){
        auto v = solve(N, A, B);
        if(v.empty()){
            cout << -1 << endl;
        } else {
            cout << v[0];
            for(int i=1;i<v.size();i++) cout << " " << v[i];
            cout << endl;
        }
    }
}