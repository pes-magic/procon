#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Info {
public:
    explicit Info(long long width=0, long long dif=0, int idx=0) : width(width), dif(dif), idx(idx) {}
    long long width, dif;
    int idx;
    bool operator < (const Info& i) const { return width > i.width; }
};

int main(){
    int N;
    long long K;
    while(cin >> N >> K){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        vector<int> src(N), dst(N), value(N);
        for(int i=0;i<N;i++){
            src[i] = dst[i] = i;
            value[i] = A[i];
        }
        for(int i=1;i<N;i++){
            if(value[src[i-1]] == A[i]){
                dst[src[i-1]] = i;
                src[i] = src[i-1];
            }
        }
        priority_queue<Info> qu;
        for(int i=0;i<N;i++){
            int e = dst[i];
            if((i == 0 || value[src[i-1]] < value[i]) && (e == N-1 || value[i] > value[e+1])){
                int dif = value[i] - 1;
                if(i > 0) dif = min(dif, value[i] - value[src[i-1]]);
                if(e < N-1) dif = min(dif, value[i] - value[e+1]);
                qu.emplace(e-src[i]+1, dif, i);
            }
            i = e;
        }
        while(K > 0){
            auto p = qu.top(); qu.pop();
            long long dec = p.width * p.dif;
            int s = src[p.idx];
            int e = dst[p.idx];
            if(K >= dec){
                value[p.idx] -= p.dif;
                if(s > 0){
                    if(value[src[s-1]] == value[p.idx]){
                        dst[src[s-1]] = dst[s];
                        src[dst[s]] = src[s-1];
                        s =  src[s-1];
                    }
                }
                if(e < N-1){
                    if(value[e+1] == value[p.idx]){
                        e = dst[s] = dst[e+1];
                        src[e] = src[s];
                    }
                }
                if((s == 0 || value[src[s-1]] < value[s]) && (e == N-1 || value[s] > value[e+1])){
                    int dif = value[s] - 1;
                    if(s > 0) dif = min(dif, value[s] - value[src[s-1]]);
                    if(e < N-1) dif = min(dif, value[s] - value[e+1]);
                    qu.emplace(e-s+1, dif, s);
                }
                K -= dec;
            } else {
                int v = value[s] - K/(e-s+1);
                int m = K%(e-s+1);
                for(int i=0;i<=e-s;i++){
                    src[s+i] = dst[s+i] = s+i;
                    value[s+i] = v - (i < m ? 1 : 0);
                }
                K = 0;
            }
        }
        for(int i=0;i<N;i++){
            for(int j=i;j<=dst[i];j++) value[j] = value[i];
            i = dst[i];
        }
        long long res = 0;
        for(int i=0;i<N;i++){
            res += 2 * value[i] + 1;
            res += (i==0 ? value[i] : abs(value[i]-value[i-1]));
        }
        res += value.back();
        cout << res << endl;
    }
}