#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class BIT {
public:
    explicit BIT(int n) : N(calcN_(n)), mVal(calcN_(n)+1, 0) {}
    void add(int idx, T val){
        for(int x=idx;x<=N;x+=x&-x) mVal[x] += val;
    }
    T sum(int idx){
        T res = 0;
        for(int x=idx;x>0;x-=x&-x) res += mVal[x];
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    const int N;
    vector<T> mVal;
};

long long inversion(const vector<int> &v){
    BIT<long long> bit(21);
    long long res = 0;
    for(int i=v.size()-1;i>=0;i--){
        res += bit.sum(v[i]-1);
        bit.add(v[i], 1);
    }
    return res;
}

const int MOD = 1000000000;

int main(){
    int K; cin >> K;
    vector<vector<long long>> num;
    vector<long long> base;
    for(int i=0;i<K;i++){
        int n; cin >> n;
        vector<int> a(n);
        for(auto& t : a) cin >> t;
        base.push_back(inversion(a));
        vector<long long> cnt(21, 0);
        for(auto& t : a) cnt[t]++;
        num.push_back(cnt);
    }
    int Q; cin >> Q;
    long long res = 0;
    vector<long long> sum(21, 0);
    for(int i=0;i<Q;i++){
        int q; cin >> q;
        --q;
        res = (res + base[q]) % MOD;
        long long s = 0;
        for(int j=20;j>=1;j--){
            res += s * num[q][j];
            res %= MOD;
            s += sum[j];
        }
        for(int j=1;j<=20;j++){
            sum[j] = (sum[j] + num[q][j]) % MOD;
        }
    }
    cout << res << endl;
}