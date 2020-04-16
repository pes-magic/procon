#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        T res = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ res = operate(res, mVal[offset+l-1]); l++; }
            if(r&1){ res = operate(res, mVal[offset+r-2]); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N;
    while(cin >> N){
        string S; cin >> S;
        vector<int> sm(N+1, 0), se(N+1, 0), sp(N+1, 0), sq(N+1, 0);
        for(int i=0;i<N;i++){
            sm[i+1] = sm[i] + (S[i] == '(' ? 1 : S[i] == ')' ? -1 : -1);
            se[i+1] = se[i] + (S[i] == '(' ? 1 : S[i] == ')' ? -1 : 0);
            sp[i+1] = sp[i] + (S[i] == '(' ? 1 : S[i] == ')' ? -1 : 1);
            sq[i+1] = sq[i] + (S[i] == '?' ? 1 : 0);
        }
        SegTree<int> segDec(N+1, N+100), segInc(N+1, N+100);
        for(int i=0;i<=N;i++){
            segDec.update(i, sm[i]);
            segInc.update(i, sp[i]);
        }
        int Q; cin >> Q;
        for(int q=0;q<Q;q++){
            auto solve = [&](){
                int L, R; cin >> L >> R;
                if((R-L)%2 == 0) return "No";
                int dif = se[R] - se[L-1];
                int numq = sq[R] - sq[L-1];
                int np = 0, nm = 0;
                if(dif > 0) nm = dif;
                else np = -dif;
                if(np + nm > numq) return "No";
                if((numq - (np+nm))%2 == 1) return "No";
                int half = (numq - (np+nm))/2;
                np += half;
                nm += half;
                int low = L-1, high = R+1;
                while(high-low > 1){
                    int mid = (low+high)/2;
                    if(sq[mid] - sq[L-1] <= np) low = mid;
                    else high = mid;
                }
                if(segInc.get(L, low+1) < sp[L-1]) return "No";
                if(segDec.get(low+1, R+1) < sm[R]) return "No";
                return "Yes";
            };
            cout << solve() << endl;
        }
    }
}