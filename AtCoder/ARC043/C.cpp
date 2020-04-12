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

long long inversionNum(const vector<int>& v){
    BIT<int> bit(v.size());
    long long res = 0;
    for(int i=v.size()-1;i>=0;i--){
        res += bit.sum(v[i]);
        bit.add(v[i], 1);
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> a(N), b(N); // 1-indexed
        for(auto& t : a) cin >> t;
        for(auto& t : b) cin >> t;
        vector<int> idx(N+1);
        for(int i=0;i<N;i++) idx[a[i]] = i+1;
        vector<int> c(N);
        for(int i=0;i<N;i++) c[i] = idx[b[i]];
        long long inv = inversionNum(c);
        if(inv%2 == 1){
            cout << -1 << endl;
            continue;
        }
        inv /= 2;
        vector<int> ord(N+1);
        for(int i=0;i<N;i++) ord[c[i]] = i+1;
        BIT<int> bit(N);
        vector<int> res;
        for(int i=1;i<=N;i++){
            long long t = ord[i] - 1 - bit.sum(ord[i]);
            bit.add(ord[i], 1);
            if(t <= inv){
                inv -= t;
                res.push_back(i);
            } else {
                int push = t - inv;
                for(int j=0;j<N;j++){
                    if(c[j] <= i) continue;
                    else {
                        res.push_back(c[j]);
                        --push;
                        if(push == 0) res.push_back(i);
                    }
                }
                break;
            }
        }
        for(int i=0;i<N;i++) res[i] = a[res[i]-1];
        cout << res[0];
        for(int i=1;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}
