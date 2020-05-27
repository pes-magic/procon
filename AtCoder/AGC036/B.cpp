#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    long long K;
    cin >> N >> K;
    vector<int> A(N);
    vector<vector<int>> pos(200001);
    for(int i=0;i<N;i++){
        cin >> A[i];
        pos[A[i]].push_back(i);
    }
    vector<int> next(N);
    for(auto& v : pos){
        for(int i=0;i<v.size();i++){
            next[v[i]] = (v[(i+1)%v.size()] + 1) % N;
        }
    }
    vector<int> res;
    long long cycle = 0, p = 0;
    while(cycle < K){
        auto ncycle = cycle;
        if(next[p] == (p+1)%N) ++ncycle;
        if(next[p] <= p) ++ncycle;
        auto npos = next[p];
        if(ncycle >  K || (ncycle == K && npos > 0)){
            res.push_back(A[p]);
            if(p == N-1){
                p = 0;
                ++cycle;
            } else {
                p++;
            }
        } else {
            cycle = ncycle;
            p = npos;
            if(cycle < K && p == 0){
                K %= cycle;
                cycle = 0;
            }
        }
    }
    for(auto& t : res) cout << t << " ";
    cout << endl;
}