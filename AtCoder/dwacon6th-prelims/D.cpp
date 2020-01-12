#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class SegTree {
public:
    explicit SegTree(int n) : N(calcN_(n)), def(0), mVal(2*calcN_(n)-1, 0) {}
    void update(int idx, T value){
        int i = N + idx - 1;
        update_(mVal[i], value);
        while(i > 0){
            i = (i-1)/2;
            mVal[i] = operate(mVal[2*i+1], mVal[2*i+2]);
        }
    }
    T get(int idx) const { return mVal[N+idx-1]; }
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
    T update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return max(a, b); }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int N;
    while(cin >> N){
        vector<int> a(N);
        vector<int> ng(N, 0);
        for(int i=0;i<N;i++){
            cin >> a[i]; --a[i];
            ng[a[i]]++;
        }
        if(N == 2){
            cout << -1 << endl;
            continue;
        }
        SegTree<int> ngcnt(N);
        SegTree<int> exist(N);
        for(int i=0;i<N;i++){
            ngcnt.update(i, ng[i]);
            exist.update(i, 1);
        }
        int prev = -1;
        vector<int> res;
        for(int i=0;i<N;i++){
            int sel = -1;
            if(i != N-1 && ngcnt.get(0, N) == N-i-1){
                int L = 0, R = N;
                while(R-L > 1){
                    int mid = (L+R)/2;
                    if(ngcnt.get(0, mid) == N-i-1) R = mid;
                    else L = mid;
                }
                sel = R-1;
            } else if (i == N-3){
                vector<int> rest;
                for(int j=0;j<N;j++) if(exist.get(j)) rest.push_back(j);
                for(int j=0;j<3;j++){
                    for(int k=j+1;k<3;k++){
                        if(a[rest[j]] == rest[k] && a[rest[k]] == rest[j]){
                            sel = rest[rest[j] == prev ? k : j];
                        }
                    }
                }
            }
            if(sel == -1){
                bool del = (prev != -1 && exist.get(prev));
                if(del) exist.update(prev, 0);
                int L = 0, R = N;
                while(R-L > 1){
                    int mid = (L+R)/2;
                    if(exist.get(0, mid)) R = mid;
                    else L = mid;
                }
                sel = R-1;
                if(del) exist.update(prev, 1);
            }
            res.push_back(sel+1);
            exist.update(sel, 0);
            ngcnt.update(sel, 0);
            prev = a[sel];
            if(exist.get(prev)){
                --ng[prev];
                ngcnt.update(prev, ng[prev]);
            }
        }
        cout << res[0];
        for(int i=1;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}