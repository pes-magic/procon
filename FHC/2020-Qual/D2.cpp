#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

const long long INF = 1LL << 60;

template<typename T>
class SegTree {
public:
    explicit SegTree(int n, T def) : N(calcN_(n)), def(def), mVal(2*calcN_(n)-1, def) {}
    void update(int idx, T value){
        int i = N + idx - 1;
        update_(mVal[i], value);
        while(i > 0){
            i = (i-1)/2;
            mVal[i] = operate(mVal[2*i+1], mVal[2*i+2]);
        }
    }
    T get(int l, int r){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        T resL = def;
        T resR = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ resL = operate(resL, mVal[offset+l-1]); l++; }
            if(r&1){ resR = operate(mVal[offset+r-2], resR); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return operate(resL, resR);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = min(data, val); }
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N, M, A, B; cin >> N >> M >> A >> B;
        --A; --B;
        vector<vector<int>> g(N);
        vector<long long> C(N);
        for(int i=0;i<N;i++){
            int p; cin >> p >> C[i];
            if(p > 0){
                --p;
                g[p].push_back(i);
                g[i].push_back(p);
            }
        }
        vector<int> dist(N, N);
        dist[B] = 0;
        queue<int> qu; qu.push(B);
        while(!qu.empty()){
            int p = qu.front(); qu.pop();
            for(auto& next : g[p]){
                if(dist[next] != N) continue;
                dist[next] = dist[p] + 1;
                qu.push(next);
            }
        }
        SegTree<long long> seg(dist[A], INF);
        int prevPos = -1;
        int curPos = A;
        seg.update(0, 0);
        vector<long long> best(M, INF);
        while(curPos != B){
            qu.push(curPos);
            int nextPos = -1;
            int idx = dist[A] - dist[curPos];
            int checked = -1;
            while(!qu.empty()){
                int p = qu.front(); qu.pop();
                int d = dist[p] - dist[curPos];
                if(2*d >= M) continue;
                if(C[p] > 0){
                    long long v = seg.get(max(0, idx-M+d), idx) + C[p];
                    if(checked < d || best[d] > v){
                        checked = d;
                        best[d] = v;
                    }
                } else {
                    if(checked < d){
                        checked = d;
                        best[d] = INF;
                    }
                }
                for(auto& next : g[p]){
                    if(next == prevPos) continue;
                    if(dist[next] < dist[curPos]){
                        nextPos = next;
                    } else if(dist[next] > dist[p]){
                        qu.push(next);
                    }
                }
            }
            for(int i=0;i<=checked;i++){
                seg.update(max(0, idx-i), best[i]);
            }
            prevPos = curPos;
            curPos = nextPos;
        }
        auto res = seg.get(max(0, dist[A]-M), dist[A]);
        printf("Case #%d: %lld\n", t, res < INF ? res : -1);
    }
}