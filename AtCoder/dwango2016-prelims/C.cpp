#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

class Node {
public:
    explicit Node(int dst, int cost, int end, int endCost) : dst(dst), cost(cost), end(end), endCost(endCost) {}
    int dst;
    int cost;
    int end;
    int endCost;
};

int main(){
    int N, M, src, dst; cin >> N >> M >> src >> dst;
    vector<vector<Node>> g(N);
    for(int i=0;i<M;i++){
        int L; cin >> L;
        vector<int> s(L);
        vector<int> w(L-1);
        for(auto& t : s) cin >> t;
        for(auto& t : w) cin >> t;
        int sum = 0;
        for(int j=0;j<L-1;j++){
            g[s[j]].emplace_back(s[j+1], w[j], s[0], sum);
            sum += w[j];
        }
        sum = 0;
        for(int j=L-2;j>=0;j--){
            g[s[j+1]].emplace_back(s[j], w[j], s.back(), sum);
            sum += w[j];
        }
    }
    vector<int> normalDist(N, 1LL << 30);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> qu;
    qu.emplace(0, dst);
    normalDist[dst] = 0;
    while(!qu.empty()){
        auto pr = qu.top(); qu.pop();
        auto curPos = pr.second;
        auto curCost = pr.first;
        for(auto& nd : g[curPos]){
            auto nextPos = nd.dst;
            auto nextCost = curCost + nd.cost;
            if(normalDist[nextPos] > nextCost){
                normalDist[nextPos] = nextCost;
                qu.emplace(nextCost, nextPos);
            }
        }
    }
    vector<int> dist(N, 1LL << 30);
    dist[dst] = 0;
    qu.emplace(0, dst);
    while(!qu.empty()){
        auto pr = qu.top(); qu.pop();
        auto curPos = pr.second;
        auto curCost = pr.first;
        for(auto& nd : g[curPos]){
            auto nextPos = nd.dst;
            auto nextCost = max(curCost + nd.cost, nd.cost + nd.endCost + normalDist[nd.end]);
            if(dist[nextPos] > nextCost){
                dist[nextPos] = nextCost;
                qu.emplace(nextCost, nextPos);
            }
        }
    }
    cout << dist[src] << endl;
}