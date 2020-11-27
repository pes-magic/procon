#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    int N, K; cin >> N >> K;
    vector<pair<int, int>> vp;
    for(int i=0;i<N;i++){
        int t; cin >> t;
        vp.emplace_back(t, i);
    }
    sort(vp.begin(), vp.end());
    vector<int> idx(N), prev(N), next(N);
    for(int i=0;i<N;i++){
        idx[vp[i].second] = i;
        prev[i] = i-1;
        next[i] = i+1;
    }
    set<pair<int, pair<int, int>>> S;
    for(int i=0;i+1<N;i++){
        S.emplace(vp[i+1].first-vp[i].first, make_pair(i, i+1));
    }
    set<pair<int, pair<int, int>>> use;
    int res = 0;
    while(use.size() < N-K){
        auto value = *S.begin();
        use.insert(value);
        res += value.first;
        S.erase(value);
    }
    cout << res << endl;
    int Q; cin >> Q;
    for(int i=0;i<Q;i++){
        int d; cin >> d;
        d = idx[d-1];
        if(prev[d] >= 0){
            auto value = make_pair(vp[d].first - vp[prev[d]].first, make_pair(prev[d], d));
            if(use.count(value)){
                res -= value.first;
                use.erase(value);
            }
            if(S.count(value)) S.erase(value);
            next[prev[d]] = next[d];
        }
        if(next[d] < N){
            auto value = make_pair(vp[next[d]].first - vp[d].first, make_pair(d, next[d]));
            if(use.count(value)){
                res -= value.first;
                use.erase(value);
            }
            if(S.count(value)) S.erase(value);
            prev[next[d]] = prev[d];
        }
        if(0 <= prev[d] && next[d] < N){
            S.emplace(vp[next[d]].first - vp[prev[d]].first, make_pair(prev[d], next[d]));
        }
        while(!use.empty() && !S.empty() && use.rbegin()->first > S.begin()->first){
            auto a = *use.rbegin();
            auto b = *S.begin();
            use.erase(a);
            use.insert(b);
            S.insert(a);
            S.erase(b);
            res += b.first - a.first;
        }
        while(use.size() < N-K-i-1){
            auto value = *S.begin();
            use.insert(value);
            res += value.first;
            S.erase(value);
        }
        while(use.size() > N-K-i-1){
            auto value = *use.rbegin();
            S.insert(value);
            res -= value.first;
            use.erase(value);
        }
        cout << res << endl;
    }
}