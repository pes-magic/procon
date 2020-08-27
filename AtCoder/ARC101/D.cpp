#include <iostream>
#include <vector>
#include <algorithm>

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

bool valid(const vector<int>& a, int thr){
    const int N = a.size();
    vector<int> sum(N+1, 0);
    vector<pair<int, int>> order;
    order.emplace_back(0, 0);
    for(int i=0;i<N;i++){
        sum[i+1] = sum[i] + (a[i] <= thr ? 1 : -1);
        order.emplace_back(sum[i+1], -(i+1));
    }
    sort(order.begin(), order.end());
    BIT<long long> bit(N+1);
    long long res = 0;
    for(auto& p : order){
        int idx = -p.second + 1;
        res += bit.sum(idx);
        bit.add(idx, 1);
    }
    return res > N*(N+1LL)/2/2;
}

int main(){
    int N; cin >> N;
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    auto vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int L = -1, R = vals.size()-1;
    while(R-L > 1){
        int mid = (L+R)/2;
        if(valid(a, vals[mid])) R = mid;
        else L = mid;
    }
    cout << vals[R] << endl;
}