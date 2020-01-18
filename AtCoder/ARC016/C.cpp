#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<double> ex(1<<N, 1e12);
        ex[(1<<N)-1] = 0.0;
        vector<int> cost(M);
        vector<vector<pair<int, int>>> list(M);
        for(int i=0;i<M;i++){
            int C; cin >> C >> cost[i];
            int d, c;
            for(int j=0;j<C;j++){
                cin >> d >> c;
                list[i].emplace_back(d-1, c);
            }
        }
        for(int i=(1<<N)-2;i>=0;i--){
            for(int j=0;j<M;j++){
                double c = cost[j];
                double div = 1.0;
                bool ok = false;
                for(auto& p : list[j]){
                    int next = i|(1<<p.first);
                    if(next == i) div -= 0.01 * p.second;
                    else { ok = true; c += 0.01 * p.second * ex[next]; }
                }
                if(ok) ex[i] = min(ex[i], c/div);
            }
        }
        printf("%.8lf\n", ex[0]);
    }
}