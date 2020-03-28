#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int X, Y, A, B, C;
    while(cin >> X >> Y >> A >> B >> C){
        vector<int> p(A), q(B), r(C);
        for(auto& t : p) cin >> t;
        for(auto& t : q) cin >> t;
        for(auto& t : r) cin >> t;
        sort(p.rbegin(), p.rend());
        sort(q.rbegin(), q.rend());
        sort(r.rbegin(), r.rend());
        long long res = 0;
        for(int i=0;i<X;i++) res += p[i];
        for(int i=0;i<Y;i++) res += q[i];
        for(int i=0;i<C;i++){
            bool checkX = (Y == 0 || (X != 0 && p[X-1] < q[Y-1]));
            if(checkX){
                if(r[i] > p[X-1]) res += r[i] - p[X-1];
                else break;
                --X;
            } else {
                if(r[i] > q[Y-1]) res += r[i] - q[Y-1];
                else break;
                --Y;
            }
            if(X == 0 && Y == 0) break;
        }
        cout << res << endl;
    }
}