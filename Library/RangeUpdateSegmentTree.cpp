// 区間更新セグメント木
// Verifyed
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
// https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_d
// https://atcoder.jp/contests/agc029/tasks/agc029_c
// https://atcoder.jp/contests/code-festival-2014-final/tasks/code_festival_final_i

template<typename T>
class RangeUpdateQuery {
public:
    explicit RangeUpdateQuery(int n, T def) : N(calcN_(n)) {
        mVal.assign(2*N+1, make_pair(-1, def));
    }
    void update(int l, int r, T value, int ts){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ mVal[offset+l-1].first = ts; mVal[offset+l-1].second = value; l++; }
            if(r&1){ mVal[offset+r-2].first = ts; mVal[offset+r-2].second = value; }
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
            res = max(mVal[i], res);
        }
        return res.second;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    const int N;
    vector<pair<int,T>> mVal;
};
