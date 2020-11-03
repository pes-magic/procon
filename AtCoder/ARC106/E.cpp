#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, K; cin >> N >> K;
    vector<int> m(2*N*K, 0);
    for(int i=0;i<N;i++){
        int a; cin >> a;
        for(int j=0;j<m.size();j++){
            if(j/a%2 == 1) m[j] |= 1<<i;
        }
    }
    int L = 0, R = 2*N*K;
    while(R-L > 1){
        int mid = (L+R)/2;
        vector<int> cnt(1<<N, 0);
        for(int i=0;i<mid;i++) cnt[m[i]]++;
        for(int i=0;i<N;i++){
            for(int j=0;j<(1<<N);j++){
                if(j&(1<<i)) cnt[j^(1<<i)] += cnt[j];
            }
        }
        bool ok = true;
        for(int j=1;j<(1<<N);j++){
            int c = 0;
            for(int i=0;i<N;i++) c += (j>>i)%2;
            if(mid - cnt[j] < c*K) ok = false;
        }
        if(ok) R = mid;
        else L = mid;
    }
    cout << R << endl;
}