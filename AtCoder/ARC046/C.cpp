#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000007;

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
        return getImpl_(l, r, 0, 0, N);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return def;
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate(a, b);
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<pair<int, int>> A(N), B(M);
        for(auto& p : A) cin >> p.first >> p.second;
        for(auto& p : B) cin >> p.first >> p.second;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        SegTree<int> seg(M, INF);
        for(int i=0;i<M;i++) seg.update(i, B[i].second);
        int res = 0;
        for(auto& p : A){
            int idx = distance(B.begin(), lower_bound(B.begin(), B.end(), make_pair(p.second, 0)));
            int m = seg.get(idx, M);
            if(m > p.first) continue;
            int L = idx, R = M;
            while(R-L > 1){
                int mid = (L+R)/2;
                if(seg.get(idx, mid) <= p.first) R = mid;
                else L = mid;
            }
            ++res;
            seg.update(L, INF);
        }
        cout << res << endl;
    }
}