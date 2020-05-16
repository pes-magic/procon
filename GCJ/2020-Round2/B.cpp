#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> solveSmall(const vector<int>& cond, vector<vector<int>>& g, int D){
    const int N = cond.size();
    vector<int> dist(N, 100000);
    vector<vector<int>> weight(N, vector<int>(N, 100000));
    dist[0] = 0;
    vector<int> decide(N, 0);
    decide[0] = 1;
    while(true){
        int low = -N;
        vector<int> next;
        for(int i=0;i<N;i++){
            if(decide[i]) continue;
            if(cond[i] > low){
                next.clear();
                low = cond[i];
            }
            if(cond[i] == low){
                next.push_back(i);
            }
        }
        if(next.empty()) break;
        int target = 0;
        for(auto& t : next){
            int maxDist = 0;
            for(int i=0;i<N;i++){
                if(!decide[i]) continue;
                target = max(target, dist[i]);
            }
        }
        ++target;
        for(auto& t : next){
            for(int i=0;i<N;i++){
                if(!decide[i]) continue;
                if(g[t][i] == -1) continue;
                weight[t][i] = weight[i][t] = target - dist[i];
            }
        }
        for(auto& t : next){
            decide[t] = 1;
            dist[t] = target;
        }
    }
    vector<int> res(D, 0);
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(g[i][j] == -1) continue;
            res[g[i][j]] = weight[i][j];
        }
    }
    return res;
}

vector<int> solve(const vector<int>& cond, vector<vector<int>>& g, int D){
    const int N = cond.size();
    vector<int> dist(N, 100000);
    vector<vector<int>> weight(N, vector<int>(N, 100000));
    dist[0] = 0;
    vector<int> decide(N, 0);
    decide[0] = 1;
    int decideNum = 1;
    while(decideNum < N){
        vector<int> next;
        for(int i=0;i<N;i++){
            if(decide[i]) continue;
            if(cond[i] == -decideNum){
                next.push_back(i);
            }
        }
        bool second = next.empty();
        if(second){
            int low = 100000;
            for(int i=0;i<N;i++){
                if(decide[i]) continue;
                if(cond[i] < 0) continue;
                if(cond[i] < low){
                    next.clear();
                    low = cond[i];
                }
                if(cond[i] == low){
                    next.push_back(i);
                }
            }
        }
        int target = 0;
        if(second){
            target = cond[next.front()];
        } else {
            for(int i=0;i<N;i++){
                if(!decide[i]) continue;
                target = max(target, dist[i]);
            }
            ++target;
        }
        for(auto& t : next){
            for(int i=0;i<N;i++){
                if(!decide[i]) continue;
                if(g[t][i] == -1) continue;
                if(target - dist[i] > 0){
                    weight[t][i] = weight[i][t] = target - dist[i];
                }
            }
        }
        for(auto& t : next){
            decide[t] = 1;
            dist[t] = target;
            ++decideNum;
        }
    }
    vector<int> res(D, 0);
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(g[i][j] == -1) continue;
            res[g[i][j]] = weight[i][j];
        }
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int C, D; cin >> C >> D;
        vector<int> cond(C, 0);
        for(int i=1;i<C;i++) cin >> cond[i];
        vector<vector<int>> g(C, vector<int>(C, -1));
        for(int i=0;i<D;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            g[a][b] = g[b][a] = i;
        }
        vector<int> res = solve(cond, g, D);
        printf("Case #%d:", t);
        for(int i=0;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}