#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<long long> a(N);
        for(auto& t : a) cin >> t;
        long long res = 0;
        vector<long long> m(N);
        while(true){
            long long add = 0;
            for(int i=0;i<N;i++){
                m[i] = a[i]/N;
                a[i] -= m[i] * N;
                add += m[i];
            }
            for(int i=0;i<N;i++) a[i] += (add - m[i]);
            if(add == 0) break;
            res += add;
        }
        cout << res << endl;
    }
}