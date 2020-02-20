// BinaryIndexedTree
// Verifyed
// https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j
// https://atcoder.jp/contests/tenka1-2017/tasks/tenka1_2017_e

// 1-indexed
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

// 転倒数
int main(){
    int N;
    while(cin >> N){
        vector<int> a(N); // 1-indexed
        for(auto& t : a) cin >> t;
        BIT<int> bit(N);
        long long res = 0;
        for(int i=N-1;i>=0;i--){
            res += bit.sum(a[i]);
            bit.add(a[i], 1);
        }
        cout << res << endl;
    }
}