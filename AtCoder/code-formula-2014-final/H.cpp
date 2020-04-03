#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class SegTreeSeq {
public:
    explicit SegTreeSeq(int n) : N(calcN_(n)), finalize(false), mSeq(2*calcN_(n)-1) {}
    void push(int idx, T value){
        if(finalize) { cerr << "Invalid operation" << endl; return; }
        mSeq[N + idx - 1].push_back(value);
    }
    int countLeq(int l, int r, const T& thr){
        if(!finalize) setup_();
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        int res = 0;
        auto calc = [&](int idx){
            return distance(mSeq[idx].begin(), upper_bound(mSeq[idx].begin(), mSeq[idx].end(), thr));
        };
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ res += calc(offset+l-1); l++; }
            if(r&1){ res += calc(offset+r-2); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return res;
    }
private:
    void setup_(){
        finalize = true;
        for(int i=N-1;i<2*N-1;i++) sort(mSeq[i].begin(), mSeq[i].end());
        for(int i=N-2;i>=0;i--){
            const auto& v1 = mSeq[2*i+1];
            const auto& v2 = mSeq[2*i+2];
            mSeq[i].assign(v1.size() + v2.size(), 0);
            merge(v1.begin(), v1.end(), v2.begin(), v2.end(), mSeq[i].begin());
        }
    }
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    const int N;
    bool finalize;
    vector<vector<T>> mSeq;
};

long long solve(int N, SegTreeSeq<int>& seg, const vector<pair<int, int>>& vp, int S){
    vector<pair<int, int>> thr;
    thr.emplace_back(1, S);
    for(int d=2;d<N;d++){
        int v = S/d;
        if(thr.back().second != v){
            thr.emplace_back(d, v);
        }
    }
    thr.emplace_back(N, 0);
    long long res = 0;
    int cnt = 0;
    for(auto& p : vp){
        for(int i=0;i+1<thr.size();i++){
            if(p.first + thr[i].first >= N) break;
            res += seg.countLeq(p.first + thr[i].first, p.first + thr[i+1].first, p.second + thr[i].second);
        }
    }
    return res;
}

int main(){
    int N, S1, S2;
    while(cin >> N >> S1 >> S2){
        vector<pair<int, int>> vp(N);
        const int M = 50000;
        SegTreeSeq<int> seg(M);
        for(auto& p : vp){
            cin >> p.first >> p.second;
            --p.first;
            seg.push(p.first, p.second);
        }
        cout << solve(M, seg, vp, S2) - solve(M, seg, vp, S1-1) << endl;
    }
}