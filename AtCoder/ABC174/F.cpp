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

struct Query {
    explicit Query(int l, int r, int id) : l(l), r(r), id(id){}
    int l, r, id;
    bool operator < (const Query& q) const { return r < q.r; }
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<int> c(N);
    for(auto& t : c){ cin >> t; --t; }
    vector<Query> vq;
    for(int i=0;i<Q;i++){
        int l, r; cin >> l >> r;
        --l;
        vq.emplace_back(l, r, i);
    }
    sort(vq.begin(), vq.end());
    vector<int> res(Q);
    vector<int> last(N, -1);
    int end = 0;
    BIT<int> bit(N);
    for(auto& q : vq){
        for(int i=end;i<q.r;i++){
            if(last[c[i]] != -1) bit.add(last[c[i]], -1);
            bit.add(i+1, 1);
            last[c[i]] = i+1;
        }
        end = q.r;
        res[q.id] = bit.sum(q.r) - bit.sum(q.l);
    }
    for(auto& t : res) cout << t << endl;
}