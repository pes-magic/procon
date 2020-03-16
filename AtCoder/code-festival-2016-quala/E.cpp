#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        int Q; cin >> Q;
        vector<int> order;
        vector<int> used(M, 0);
        vector<int> q(Q);
        for(auto& t : q){ cin >> t; --t; }
        reverse(q.begin(), q.end());
        for(auto& t : q){
            if(used[t]) continue;
            used[t] = 1;
            order.push_back(t);
        }
        for(int i=0;i<M;i++) if(!used[i]) order.push_back(i);
        reverse(order.begin(), order.end());
        vector<int> idx(M);
        for(int i=0;i<M;i++) idx[order[i]] = i;
        vector<int> stock(M, 0);
        for(int i=0;i<M;i++){
            if(i+1 == M || order[i] < order[i+1]){
                stock[i] = N;
                break;
            }
        }
        reverse(q.begin(), q.end());
        for(auto& t : q){
            int p = idx[t];
            if(p == 0) continue;
            if(stock[p-1] > 0){
                --stock[p-1];
                ++stock[p];
            }
        }
        cout << (stock.back() >= N ? "Yes" : "No") << endl;
    }
}