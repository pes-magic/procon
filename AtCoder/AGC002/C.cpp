#include <iostream>
#include <vector>

using namespace std;

void solve(const vector<int>& a, int L){
    for(int i=1;i<a.size();i++){
        if(a[i-1]+a[i] < L) continue;
        cout << "Possible" << endl;
        for(int j=1;j<i;j++) cout << j << endl;
        for(int j=a.size()-1;j>=i;j--) cout << j << endl;
        return;
    }
    cout << "Impossible" << endl;
}

int main(){
    int N, L;
    while(cin >> N >> L){
        vector<int> a(N);
        for(auto& t : a) cin >> t;
        solve(a, L);
    }
}