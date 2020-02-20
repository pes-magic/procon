#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

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
    void clean(){
        fill(mVal.begin(), mVal.end(), 0);
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

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> lines(N, vector<int>(3));
        for(auto& v : lines) cin >> v[0] >> v[1] >> v[2];
        double res[2];
        for(int i=0;i<2;i++){
            sort(lines.begin(), lines.end(), [](const vector<int>& a, const vector<int>& b){ return (double)a[0]/a[1] < (double)b[0]/b[1]; });
            double L = -1e10, R = 1e10;
            vector<int> v(N);
            auto val = [](const vector<int>& l, double x){ return ((double)l[2] - x * l[0])/l[1]; };
            for(int i=0;i<N;i++) v[i] = i;
            BIT<int> bit(N);
            long long thr = (N*(N-1LL)/2+1)/2;
            for(int _=0;_<100;_++){
                bit.clean();
                double mid = 0.5*(L+R);
                sort(v.begin(), v.end(), [&](int a, int b){ return val(lines[a], mid) < val(lines[b], mid); });
                long long cnt = 0;
                for(int i=N-1;i>=0;i--){
                    cnt += bit.sum(v[i]+1);
                    bit.add(v[i]+1, 1);
                }
                if(cnt < thr) L = mid;
                else R = mid;
            }
            res[i] = 0.5*(L+R);
            for(auto& v : lines) swap(v[0], v[1]);
        }
        printf("%.10lf %.10lf\n", res[0], res[1]);
    }
}