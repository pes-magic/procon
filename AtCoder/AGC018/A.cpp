#include <iostream>

using namespace std;

int gcd(int a, int b){ return a%b ? gcd(b, a%b) : b; }

int main(){
    int N, K;
    while(cin >> N >> K){
        int g = 0;
        cin >> g;
        int m = g;
        for(int i=1;i<N;i++){
            int t; cin >> t;
            m = max(t, m);
            g = gcd(g, t);
        }
        if(K <= m && K%g == 0){
            cout << "POSSIBLE" << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
}