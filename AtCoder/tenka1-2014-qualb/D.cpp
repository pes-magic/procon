#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solve(const vector<int>& A, const vector<vector<int>>& B){
    const int N = A.size();
    vector<int> weight = A;
    sort(weight.begin(), weight.end());
    weight.erase(unique(weight.begin(), weight.end()), weight.end());
    vector<vector<int>> g(N);
    vector<int> maxj(N, -1), minj(N, B.size()), maxk(N, -1), mink(N, B[0].size());
    for(int i=0;i<N;i++){
        for(int j=0;j<B.size();j++){
            for(int k=0;k<B[j].size();k++){
                if(B[j][k] != i) continue;
                maxj[i] = max(maxj[i], j);
                minj[i] = min(minj[i], j);
                maxk[i] = max(maxk[i], k);
                mink[i] = min(mink[i], k);
            }
        }
        int checked = 0;
        for(int j=minj[i];j<=maxj[i];j++){
            for(int k=mink[i];k<=maxk[i];k++){
                if(B[j][k] != i && !(checked&(1<<B[j][k]))){
                    g[B[j][k]].push_back(i);
                    checked |= (1 << B[j][k]);
                }
            }
        }
    }
    vector<int> req(N, 0);
    for(int i=0;i<N;i++){
        queue<int> qu; qu.push(i);
        while(!qu.empty()){
            int t = qu.front(); qu.pop();
            for(auto& nxt : g[t]){
                if(req[i]&(1<<nxt)) continue;
                req[i] |= (1<<nxt);
                qu.push(nxt);
            }
        }
    }
    vector<int> avoid(N, 0);
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(req[i]&(1<<j)) continue;
            if(req[j]&(1<<i)) continue;
            if(max(minj[i], minj[j]) > min(maxj[i], maxj[j])) continue;
            if(max(mink[i], mink[j]) > min(maxk[i], maxk[j])) continue;
            avoid[i] |= 1 << j;
            avoid[j] |= 1 << i;
        }
    }
    vector<int> dp(1<<N, 0);
    dp[0] = 1;
    queue<int> qu; qu.push(0);
    for(auto& w : weight){
        int see = 0;
        for(auto& t : A) if(t == w) ++see;
        queue<int> next;
        while(!qu.empty()){
            int v = qu.front(); qu.pop();
            vector<int> ok;
            for(int i=0;i<N;i++){
                if(v&(1<<i)) continue;
                if((req[i]&v) == req[i]) ok.push_back(i);
            }
            if(ok.size() < see) continue;
            vector<int> use(ok.size(), 0);
            for(int i=ok.size()-see;i<ok.size();i++) use[i] = 1;
            do {
                int msk = v;
                for(int i=0;i<ok.size();i++) if(use[i]) msk |= (1 << ok[i]);
                bool valid = true;
                for(int i=0;i<ok.size();i++) if(use[i] && ((msk^v)&(avoid[ok[i]]))) valid = false;
                if(valid && !dp[msk]){
                    next.push(msk);
                    dp[msk] = 1;
                }
            } while(next_permutation(use.begin(), use.end()));
        }
        qu = next;
    }
    return dp.back();
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        int H, W; cin >> H >> W;
        vector<vector<int>> B(H, vector<int>(W));
        for(auto& v : B){
            for(auto& t : v) cin >> t;
        }
        cout << solve(A, B) << endl;
    }
}