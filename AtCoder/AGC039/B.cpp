#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> search(int start, const vector<string>& S){
    const int N = S.size();
    vector<int> dist(N, N);
    queue<int> qu; qu.push(start);
    dist[start] = 0;
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(int t=0;t<N;t++){
            if(S[p][t] == '0') continue;
            if(dist[t] > dist[p] + 1){
                dist[t] = dist[p] + 1;
                qu.push(t);
            }
        }
    }
    return dist;
}

int solve(const vector<string>& S){
    const int N = S.size();
    vector<int> c(N, -1);
    c[0] = 0;
    queue<int> qu; qu.push(0);
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(int t=0;t<N;t++){
            if(S[p][t] == '0') continue;
            if(c[t] != -1){
                if(c[t] == c[p]) return -1;
                continue;
            }
            c[t] = 1 - c[p];
            qu.push(t);
        }
    }
    int res = 0;
    for(int i=0;i<N;i++){
        auto d = search(i, S);
        res = max(res, *max_element(d.begin(), d.end()));
    }
    return res + 1;
}

int main(){
    int N; cin >> N;
    vector<string> S(N);
    for(auto& s : S) cin >> s;
    cout << solve(S) << endl;
}