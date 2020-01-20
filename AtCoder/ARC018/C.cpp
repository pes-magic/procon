#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        int x, a, p;
        cin >> x >> a >> p;
        if(a % p == 0){
            cout << (x >= p ? 2*(N-1) : 0) << endl;
        } else {
            vector<pair<int, int>> vp;
            vp.emplace_back(x, 0);
            for(int i=1;i<N*M;i++){
                x = (x+a)%p;
                vp.emplace_back(x, i);
            }
            sort(vp.begin(), vp.end());
            vector<vector<int>> cnt(N, vector<int>(M, 0));
            long long res = 0;
            for(int i=0;i<N*M;i++){
                cnt[i/M][vp[i].second%M]++;
                res += abs(vp[i].second/M - i/M);
            }
            for(auto& v : cnt){
                queue<int> quA, quB;
                for(int i=0;i<M;i++){
                    quA.push(i);
                    for(int j=0;j<v[i];j++) quB.push(i);
                    while(!quA.empty() && !quB.empty()){
                        res += abs(quA.front() - quB.front());
                        quA.pop();
                        quB.pop();
                    }
                }
            }
            cout << res << endl;
        }
    }
}