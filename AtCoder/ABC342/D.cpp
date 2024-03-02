#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<long long> cnt(200000, 0);
    for(int i=0;i<N;i++){
        int a; cin >> a;
        for(int j=2;j*j<=a;j++){
            while(a%(j*j) == 0){
                a /= j*j;
            }
        }
        cnt[a]++;
    }
    long long res = cnt[0] * (N-cnt[0]);
    for(int i=0;i<200000;i++){
        res += cnt[i] * (cnt[i]-1) / 2;
    }
    cout << res << endl;
}