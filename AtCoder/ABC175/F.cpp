#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const long long INF = 1LL << 60;

struct Node {
    explicit Node(int idx, int pos, long long cost) : idx(idx), pos(pos), cost(cost) {}
    int idx, pos;
    long long cost;
    bool operator > (const Node& nd) const { return cost > nd.cost; }
};

int main(){
    int N; cin >> N;
    vector<string> S(2*N);
    vector<long long> C(2*N);
    for(int i=0;i<N;i++){
        cin >> S[2*i];
        S[2*i+1] = S[2*i];
        reverse(S[2*i+1].begin(), S[2*i+1].end());
        cin >> C[2*i];
        C[2*i+1] = C[2*i];
    }
    vector dist(2*N, vector(21, INF));
    priority_queue<Node, vector<Node>, greater<Node>> qu;
    for(int i=0;i<2*N;i++){
        qu.emplace(i, 0, C[i]);
        dist[i][0] = C[i];
    }
    long long res = INF;
    while(!qu.empty()){
        Node nd = qu.top(); qu.pop();
        const string& s = S[nd.idx];
        bool end = true;
        for(int i=0;i+nd.pos<s.size()-i-1;i++){
            if(s[i+nd.pos] != s[s.size()-i-1]) end = false;
        }
        if(end){
            res = min(res, nd.cost);
        }
        for(int i=1-nd.idx%2;i<2*N;i+=2){
            int l = min<int>(s.size() - nd.pos, S[i].size());
            bool ok = true;
            for(int j=0;j<l;j++){
                if(s[nd.pos+j] != S[i][j]) ok = false;
            }
            if(!ok) continue;
            int nidx = (nd.pos + l == s.size() ? i : nd.idx);
            int npos = (nd.pos + l == s.size() ? l : nd.pos + l);
            long long ncost = dist[nd.idx][nd.pos] + C[i];
            if(ncost < dist[nidx][npos]){
                dist[nidx][npos] = ncost;
                qu.emplace(nidx, npos, ncost);
            }
        }
    }
    cout << (res < INF ? res : -1) << endl;
}
