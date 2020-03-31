#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class BipartiteMatch {
public:
    explicit BipartiteMatch(int N, int M) :
        N(N), M(M), g(N+M), match(N+M, -1), visit(N+M, 0)
    {}
public:
    void addEdge(int a, int b){
        g[a].push_back(b+N);
        g[b+N].push_back(a);
    }
    int maximumMatch(){
        int res = 0;
        fill(match.begin(), match.end(), -1);
        for(int i=0;i<N;i++){
            fill(visit.begin(), visit.end(), 0);
            if(search_(i)) ++res;
        }
        return res;
    }
    int getMatch(int t) const { return t < N ? match[t] - N : match[t]; }
private:
    bool search_(int u){
        if(u < 0) return true;
        for(auto next : g[u]){
            if(visit[next]) continue;
            visit[next] = 1;
            if(search_(match[next])){
                match[u] = next, match[next] = u;
                return true;
            }
        }
        return false;
    }
private:
    const int N, M;
    vector<vector<int>> g;
    vector<int> match;
    vector<int> visit;
};

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> a(N, vector<int>(3));
        for(auto& v : a){
            for(auto& t : v) cin >> t;
        }
        vector<int> w;
        vector<pair<int, int>> pr;
        for(auto& v : a){
            for(int i=0;i<3;i++){
                int base = v[(i+1)%3] * v[(i+2)%3];
                for(int j=1;j<=v[i]-1;j++){
                    w.push_back(j*base);
                    pr.emplace_back(j*base, (v[i]-j)*base);
                }
            }
        }
        sort(w.begin(), w.end());
        w.erase(unique(w.begin(), w.end()), w.end());
        map<int, int> idx;
        for(int i=0;i<w.size();i++) idx[w[i]] = i;
        BipartiteMatch bm(w.size(), w.size());
        for(auto& p : pr){
            bm.addEdge(idx[p.first], idx[p.second]);
        }
        cout << (2*w.size() - bm.maximumMatch()) << endl;
    }
}