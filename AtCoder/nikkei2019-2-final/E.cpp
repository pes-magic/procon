#include <iostream>
#include <vector>
#include <string>
#include <set>
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

int main(){
    int N, M, Q;
    while(cin >> N >> M >> Q){
        string S; cin >> S;
        S = "1" + S + "1";
        set<int> bit;
        SegTreeSeq<int> seg(N+1);
        for(int i=0;i<S.size();i++) if(S[i] == '1') bit.insert(i);
        int score = 0;
        for(int i=0;i<M;i++){
            int L, R; cin >> L >> R;
            if(*bit.lower_bound(L) <= R) ++score;
            seg.push(L, R);
        }
        for(int i=0;i<Q;i++){
            int x; cin >> x;
            if(S[x] == '1') bit.erase(x);
            auto it = bit.upper_bound(x);
            int R = *it - 1;
            --it;
            int L = *it + 1;
            int dif = seg.countLeq(L, x+1, R) - seg.countLeq(L, x+1, x-1);
            if(S[x] == '0'){
                score += dif;
                bit.insert(x);
                S[x] = '1';
            } else {
                score -= dif;
                S[x] = '0';
            }
            cout << score << endl;
        }
    }
}