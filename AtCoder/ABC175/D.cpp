#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1LL << 60;

int main(){
    int N, K; cin >> N >> K;
    vector<int> P(N);
    vector<long long> C(N);
    for(auto& t : P){ cin >> t; --t; }
    for(auto& t : C) cin >> t;
    long long res = -INF;
    for(int i=0;i<N;i++){
        int loop = 0;
        long long loopCost = 0;
        int pos = i;
        do {
            ++loop;
            loopCost += C[pos];
            pos = P[pos];
        } while(pos != i);
        long long partMx = 0;
        int part = K%loop;
        if(part == 0) part = loop;
        long long curCost = 0;
        for(int j=0;j<loop;j++){
            curCost += C[pos];
            if(j < K) res = max(res, curCost);
            if(j < part) partMx = max(partMx, curCost);
            pos = P[pos];
        }
        if(K >= loop && loopCost > 0) res = max(res, (K/loop-(part==loop ? 1 : 0))*loopCost + partMx);
    }
    cout << res << endl;
}