#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    int N, L;
    while(cin >> N >> L){
        vector<long long> a(N), b(N), c(N);
        for(int i=0;i<N;i++) cin >> a[i] >> b[i] >> c[i];
        for(int i=1;i<N;i++){
            b[i] += b[i-1];
            c[i] += c[i-1];
        }
        long long low = 0, high = 0;
        for(int i=0;i<N-1;i++){
            a[i] = a[i+1] - a[i];
            low = min(c[i]-b[i], low);
            high = max(c[i]-b[i], high);
        }
        a.back() = L - a.back();
        --low;
        ++high;
        auto calc = [&](long long m){
            long long res = abs(m) * a.back();
            for(int i=0;i<N-1;i++){
                res += abs(c[i]-(b[i]+m)) * a[i];
            }
            return res;
        };
        while(high-low > 2){
            long long midL = (2*low+high)/3;
            long long midR = (low+2*high)/3;
            if(calc(midL) > calc(midR)) low = midL;
            else high = midR;
        }
        long long res = calc(low);
        for(auto i=low+1;i<=high;i++) res = min(res, calc(i));
        cout << res << endl;
    }
}