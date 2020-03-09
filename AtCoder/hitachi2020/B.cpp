#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int A, B, M;
    while(cin >> A >> B >> M){
        vector<int> a(A), b(B);
        for(auto& t : a) cin >> t;
        for(auto& t : b) cin >> t;
        int res = *min_element(a.begin(), a.end()) + *min_element(b.begin(), b.end());
        for(int i=0;i<M;i++){
            int x, y, c; cin >> x >> y >> c;
            res = min(res, a[x-1] + b[y-1] - c);
        }
        cout << res << endl;
    }
}