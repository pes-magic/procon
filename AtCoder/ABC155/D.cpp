#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N; long long K;
    while(cin >> N >> K){
        vector<long long> P, M;
        for(int i=0;i<N;i++){
            int A; cin >> A;
            if(A >= 0) P.push_back(A);
            else M.push_back(-A);
        }
        sort(P.begin(), P.end());
        sort(M.begin(), M.end());
        long long minus = (long long)P.size() * M.size();
        if(K <= minus){
            long long L = 0, R = 1LL << 61;
            while(R-L > 1){
                long long cnt = 0;
                long long mid = (L+R)/2;
                for(auto& m : M){
                    cnt += P.size() - distance(P.begin(), lower_bound(P.begin(), P.end(), (mid+m-1)/m));
                }
                if(cnt >= K) L = mid;
                else R = mid;
            }
            cout << -L << endl;
        } else {
            K -= minus;
            long long L = -1, R = 1LL << 61;
            while(R-L > 1){
                long long cnt = 0;
                long long mid = (L+R)/2;
                auto check = [&](const vector<long long>& v){
                    int idx = v.size() - 1;
                    for(int i=0;i<v.size();i++){
                        while(idx >= 0 && v[i] * v[idx] > mid) --idx;
                        cnt += max(0, idx - i);
                    }
                };
                check(M);
                check(P);
                if(cnt >= K) R = mid;
                else L = mid;
            }
            cout << R << endl;
        }
    }
}