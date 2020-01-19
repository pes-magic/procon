#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<long long> getPrime(int maxN){
    vector<int> p(maxN+1, 1);
    vector<long long> res(1, 2);
    for(int i=3;i<=maxN;i+=2){
        if(!p[i]) continue;
        res.push_back(i);
        for(int j=2*i;j<=maxN;j+=i) p[j] = 0;
    }
    return res;
}

int main(){
    auto primes = getPrime(100000);
    map<long long, int> sqr;
    for(auto& p : primes) sqr[p*p] = p;
    int N;
    while(cin >> N){
        vector<pair<pair<long long, long long>, int>> vp;
        for(int i=0;i<N;i++){
            long long s; cin >> s;
            long long a[3] = {1, 1, 1};
            for(int j=0;j<primes.size();j++){
                if(primes[j] * primes[j] * primes[j] > s) break;
                int cnt = 0;
                while(s % primes[j] == 0){
                    cnt = (cnt == 2 ? 0 : cnt+1);
                    s /= primes[j];
                }                
                a[cnt] *= primes[j];
            }
            if(sqr.count(s)){
                a[2] *= sqr[s];
            } else {
                a[1] *= s;
            }
            bool rev =(a[1] > a[2]);
            if(rev) swap(a[1], a[2]);
            vp.emplace_back(make_pair(a[1], a[2]), rev ? -1 : 1);
        }
        sort(vp.begin(), vp.end());
        int res = 0;
        for(int i=0;i<vp.size();){
            int j = i;
            int a = 0, b = 0;
            while(j < vp.size() && vp[i].first == vp[j].first){
                if(vp[j].second == 1) a++;
                else b++;
                ++j;
            }
            if(vp[i].first.first == vp[i].first.second) ++res;
            else res += max(a, b);
            i = j;
        }
        cout << res << endl;
    }
}