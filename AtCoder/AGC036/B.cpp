#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    long long K;
    while(cin >> N >> K){
        vector<int> a(N);
        vector<vector<int>> A(200001);
        for(int i=0;i<N;i++){
            cin >> a[i];
            A[a[i]].push_back(i);
        }
        vector<int> next(N);
        for(auto& v : A){
            const int n = v.size();
            for(int i=0;i<n;i++){
                next[v[i]] = (v[(i+1)%n]+1)%N;
            }
        }
        int cycle = 0;
        int cur = 0;
        while(true){
            if(next[cur] <= cur+1) ++cycle;
            if(cur == N-1 && next[cur] == 0) ++cycle;
            cur = next[cur];
            if(cur == 0) break;
        }
        K %= cycle;
        cycle = 0;
        vector<int> res;
        if(K > 0){
            while(true){
                if(next[cur] <= cur+1){
                    if(cycle+1 == K){
                        if(cur != N-1 && next[cur] == 0) break;
                        res.push_back(a[cur]);
                        ++cur;
                        if(cur == N) break;
                        continue;
                    }
                    ++cycle;
                }
                cur = next[cur];
            }
        }
        if(!res.empty()) cout << res[0];
        for(int i=1;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}