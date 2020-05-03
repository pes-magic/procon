#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N, D; cin >> N >> D;
        vector<long long> A(N);
        for(auto& a : A) cin >> a;
        sort(A.begin(), A.end());
        int res = D - 1;
        for(int d=1;d<=D/2;d++){
            map<long long, int> S;
            vector<long long> vl;
            for(auto& a : A){
                if(!S.count(d*a)) S[d*a] = 0;
                S[d*a]++;
                vl.push_back(d*a);
            }
            for(auto& a : A){
                int reduce = 0;
                int piece = 0;
                int sum = 0;
                auto it = vl.begin();
                for(int i=1;i<=D && sum < D && it != vl.end();i++){
                    it = lower_bound(it, vl.end(), i*a);
                    sum += distance(it, vl.end());
                }
                if(sum < D) break;
                for(int i=1;i<=D;i++){
                    if(!S.count(i*a)) continue;
                    int num = S[i*a];
                    reduce += min(num, (D-piece)/i);
                    piece += i * num;
                    if(piece >= D) break;
                }
                res = min(res, D-reduce);
            }
        }
        printf("Case #%d: %d\n", t, res);
    }
}