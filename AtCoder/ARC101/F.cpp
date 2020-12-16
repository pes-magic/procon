#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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
    inline void update_(T& data, T val) { data = (data+val)%MOD; }
    const int N;
    vector<T> mVal;
};


int main(){
    int N, M; cin >> N >> M;
    vector<int> x(N), y(M);
    for(auto& t : x) cin >> t;
    for(auto& t : y) cin >> t;
    int seek = 0;
    vector<pair<int, int>> vp;
    for(auto& t : x){
        while(seek+1 < y.size() && y[seek+1] < t) ++seek;
        if(seek == y.size()-1) break;
        if(t < y[seek]) continue;
        vp.emplace_back(t-y[seek], y[seek+1]-t);
    }
    sort(vp.begin(), vp.end());
    vp.erase(unique(vp.begin(), vp.end()), vp.end());
    vector<int> xc, yc;
    for(auto& p : vp){
        xc.push_back(p.first);
        yc.push_back(p.second);
    }
    sort(xc.begin(), xc.end());
    xc.erase(unique(xc.begin(), xc.end()), xc.end());
    sort(yc.begin(), yc.end());
    yc.erase(unique(yc.begin(), yc.end()), yc.end());
    map<int, int> xIdx, yIdx;
    for(int i=0;i<xc.size();i++) xIdx[xc[i]] = i;
    for(int i=0;i<yc.size();i++) yIdx[yc[i]] = i;
    vector<vector<int>> point(xc.size());
    for(auto& p : vp) point[xIdx[p.first]].push_back(yIdx[p.second]);
    RangeAddQuery<int> seg(yc.size()+1);
    seg.update(0, yc.size()+1, 1);
    for(int i=(int)point.size()-1;i>=0;i--){
        vector<int> add(point[i].size(), 0);
        add.back() = seg.get(point[i].back()+1);
        for(int j=(int)point[i].size()-2;j>=0;j--){
            add[j] = (add[j+1] + seg.get(point[i][j]+1)) % MOD;
        }
        seg.update(0, point[i][0]+1, add[0]);
        for(int j=1;j<point[i].size();j++){
            seg.update(point[i][j-1]+1, point[i][j]+1, add[j]);
        }
    }
    cout << seg.get(0) << endl;
}

