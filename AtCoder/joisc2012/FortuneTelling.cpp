#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

template<typename T>
class LazySegTree {
public:
    explicit LazySegTree(const vector<int>& v) : N(calcN_(v.size())) {
        mVal.assign(2*N-1, 0);
        mSum.assign(2*N-1, 0);
        for(int i=0;i<v.size();i++) mSum[i+N-1] = v[i];
        for(int i=N-2;i>=0;i--) mSum[i] = mSum[2*i+1] + mSum[2*i+2];
        mFlip.assign(2*N-1, 0);
    }
    void update(int l, int r){
        updateImpl_(l, r, 0, 0, N);
    }
    T get(int l, int r){
        return getImpl_(l, r, 0, 0, N);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void updateImpl_(int l, int r, int idx, int rangeL, int rangeR){
        eval_(idx, rangeL, rangeR);
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            setLazy_(idx);
            eval_(idx, rangeL, rangeR);
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, 2*idx+2, rangeM, rangeR);
            mVal[idx] = operate_(mVal[2*idx+1], mVal[2*idx+2]);
        }
    }
    void setLazy_(int idx){
        mFlip[idx] ^= 1;
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return 0;
        eval_(idx, rangeL, rangeR);
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate_(a, b);
    }
    void eval_(int idx, int rangeL, int rangeR){
        if(!mFlip[idx]) return;
        mVal[idx] = mSum[idx] - mVal[idx];
        if(idx < N-1){
            setLazy_(2*idx+1);
            setLazy_(2*idx+2);
        }
        mFlip[idx] = 0;
    }
    T operate_(T a, T b) const { return a + b; }
    const int N;
    vector<T> mVal;
    vector<T> mSum;
    vector<int> mFlip;
};

int main(){
    int N, M, K; cin >> N >> M >> K;
    vector<int> x, y;
    vector<pair<int, pair<int, int>>> query;
    for(int i=0;i<K;i++){
        int a, b, c, d; cin >> a >> b >> c >> d;
        query.emplace_back(a, make_pair(c, d+1));
        query.emplace_back(b+1, make_pair(c, d+1));
        x.push_back(c);
        x.push_back(d+1);
    }
    sort(query.begin(), query.end());
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    map<int, int> xIdx;
    for(int i=0;i<x.size();i++) xIdx[x[i]] = i;
    vector<int> interval(x.size()-1);
    for(int i=0;i+1<x.size();i++) interval[i] = x[i+1] - x[i];
    LazySegTree<long long> seg(interval);
    long long res = N*(long long)M;
    int prevY = query[0].first;
    for(auto& q : query){
        if(q.first != prevY){
            res -= seg.get(0, x.size()-1) * (q.first - prevY);
            prevY = q.first;
        }
        seg.update(xIdx[q.second.first], xIdx[q.second.second]);
    }
    cout << res << endl;
}