// 区間更新セグメント木
// Verifyed
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
// https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_d

template<typename T>
class RangeUpdateQuery {
public:
    explicit RangeUpdateQuery(int n, T def) : N(calcN_(n)) {
        mVal.assign(2*N+1, make_pair(-1, def));
    }
    void update(int l, int r, T value, int ts){
        updateImpl_(l, r, make_pair(ts, value), 0, 0, N);
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
    void updateImpl_(int l, int r, pair<int, T> value, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            mVal[idx] = value;
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
        }
    }
    const int N;
    vector<pair<int,T>> mVal; 
};

int main(){
    int n, q;
    while(cin >> n >> q){
        const int INF = 0x7FFFFFFF;
        RangeUpdateQuery<int> ruq(n, INF);
        for(int i=0;i<q;i++){
            int c; cin >> c;
            if(c == 0){
                int s, t, x; cin >> s >> t >> x;
                ruq.update(s, t+1, x, i);
            } else {
                int p; cin >> p;
                cout << ruq.get(p) << endl;
            }
        }
    }
}
