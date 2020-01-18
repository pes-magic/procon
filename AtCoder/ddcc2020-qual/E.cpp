#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    string res(2*N, '?');
    cout << "?";
    for(int i=1;i<=N;i++) cout << " " << i;
    cout << endl;
    string query0; cin >> query0;
    int L = 0, R = N;
    while(R - L > 1){
        cout << "?";
        int mid = (L+R)/2;
        for(int i=1;i<=N;i++) cout << " " << i+mid;
        cout << endl;
        string q; cin >> q;
        if(query0 == q) L = mid;
        else R = mid;
    }
    res[L] = query0[0];
    res[L+N] = (res[L] == 'B' ? 'R' : 'B');
    auto calcIdx = [&](int idx){
        while(idx > 2*N) idx -= 2*N;
        return idx;
    };
    for(int i=L;i<=L+N;i+=N){
        for(int j=2;j<=N;j++){ 
            cout << "? " << calcIdx(i+j);
            for(int k=2;k<=N;k++){
                cout << " " << calcIdx(i+k+N);
            }
            cout << endl;
            string q; cin >> q;
            res[(i+j-1)%(2*N)] = q[0];
        }
    }
    cout << "! " << res << endl;
}