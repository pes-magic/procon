#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

template<typename T>
class RangeAddQuery {
public:
    explicit RangeAddQuery(int n) : N(calcN_(n)) {
        mVal.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ update_(mVal[offset+l-1], value); l++; }
            if(r&1){ update_(mVal[offset+r-2], value); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            update_(res, mVal[i]);
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    inline void update_(T& data, T val) { data = (data + val) % MOD; }
    const int N;
    vector<T> mVal;
};

int maxSegment(const string& S){
    char c = S[0];
    bool first = true;
    int cnt = 0;
    int res = MOD;
    for(auto& s : S){
        if(c == s) ++cnt;
        else {
            if(first || cnt%2 == 1){
                res = min(res, cnt/2+1);
                first = false;
            }
            cnt = 0;
        }
    }
    return res < MOD ? res : -1;
}

int solve(const string& S, int N){
    int seg = maxSegment(S);
    if(seg != -1 && N%2 == 1) return 0;
    long long res = 0;
    if(seg == -1){
        RangeAddQuery<long long> raq(N);
        raq.update(0, 1, 1);
        for(int i=0;i<N;i++){
            auto a = raq.get(i);
            raq.update(i+2, N, a);
        }
        res = 1;
        for(int i=N-2;i>=0;i--){
            res = (res + raq.get(i) * (N-i)) % MOD;
        }
    } else {
        seg = min(seg, N/2);
        RangeAddQuery<long long> raq(N/2);
        raq.update(0, 1, 1);
        for(int i=0;i<N/2;i++){
            auto a = raq.get(i);
            raq.update(i+1, i+1+seg, a);
        }
        for(int i=N/2-1;i>=N/2-seg;i--){
            res = (res + raq.get(i) * 2 * (N/2-i)) % MOD;
        }
    }
    return res;
}

int main(){
    int N, M; cin >> N >> M;
    string S; cin >> S;
    cout << solve(S, N) << endl;
}
