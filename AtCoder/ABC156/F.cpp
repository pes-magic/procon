#include <iostream>
#include <vector>

using namespace std;

int main(){
    int k, q;
    while(cin >> k >> q){
        vector<int> d(k);
        for(auto& t : d) cin >> t;
        for(int _=0;_<q;_++){
            long long n, x, m; cin >> n >> x >> m;
            if(d.empty()){
                cout << 0 << endl;
                continue;
            }
            long long sum = 0;
            for(auto& t : d) sum += (t%m ? t%m : m);
            long long e = x + (n-1)/k * sum;
            for(int i=0;i<(n-1)%k;i++){
                e += (d[i]%m ? d[i]%m : m);
            }
            cout << (n-1)-e/m+x/m << endl;
        }
    }
}