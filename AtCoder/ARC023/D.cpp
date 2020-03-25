#include <iostream>
#include <vector>
#include <map>

using namespace std;

int gcd(int a, int b){ return a%b ? gcd(b, a%b) : b; }

map<int, long long> solve(const vector<int>& a){
    const int n = a.size();
    const int b = 256;
    vector<int> blk;
    for(int i=0;i<n;i+=b){
        int g = a[i];
        for(int j=i+1;j<min(n, i+b);j++) g = gcd(g, a[j]);
        blk.emplace_back(g);
    }
    map<int, long long> res;
    for(int i=0;i<n;i++){
        int src = i;
        int cur = a[i];
        int seg = i/b;
        for(int j=i+1;j<n;j++){
            if(seg != j/b){
                int nxt = gcd(cur, blk[j/b]);
                if(nxt == cur){
                    j += b-1;
                    continue;
                }
                seg = j/b;
            }
            int nxt = gcd(cur, a[j]);
            if(cur != nxt){
                if(!res.count(cur)) res[cur] = 0;
                res[cur] += j-src;
                src = j;
                cur = nxt;
            }
        }
        if(!res.count(cur)) res[cur] = 0;
        res[cur] += n-src;
    }
    return res;
}

int main(){
    int n, m;
    while(cin >> n >> m){
        vector<int> a(n);
        for(auto& t : a) cin >> t;
        auto res = solve(a);
        for(int i=0;i<m;i++){
            int b; cin >> b;
            cout << res[b] << endl;
        }
    }
}