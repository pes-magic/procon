#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <chrono>

using namespace std;

unsigned int xor32(){
    static unsigned int y = 2463534242;
    y = y ^ (y << 13); y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

int main(){
    int D; cin >> D;
    vector<int> c(26, 0);
    for(auto& t : c) cin >> t;
    vector s(D, vector(26, 0));
    for(auto& v : s){
        for(auto& t : v) cin >> t;
    }
    vector<int> last(26, 0);
    vector<set<int>> days(26);
    for(int i=0;i<26;i++){
        days[i].insert(0);
        days[i].insert(D+1);
    }
    vector<int> select(D+1, -1);
    long long score = 0;
    for(int i=1;i<=D;i++){
        int t = -1;
        long long best = 0;
        for(int j=0;j<26;j++){
            long long cur = s[i-1][j];
            for(int k=0;k<26;k++){
                if(j==k) continue;
                cur -= c[k] * (i - last[k]);
            }
            if(t == -1 || best < cur){
                t = j;
                best = cur;
            }
        }
        days[t].insert(i);
        select[i] = t;
        last[t] = i;
        score += best;
    }
    const double startTemp = 50;
    const double endTemp = 5;
    auto res = select;
    double bestScore = score;
    auto start = chrono::system_clock::now();
    const double tl = 1900;
    while(true){
        auto cur = chrono::system_clock::now();
        auto time = chrono::duration_cast<chrono::milliseconds>(cur-start).count();
        if(time > tl) break;
        const double temp = time/tl * (endTemp - startTemp) + startTemp;
        for(int i=0;i<100000;i++){
            int d = xor32()%D + 1;
            int q = xor32()%26;
            long long sub = 0;
            sub -= s[d-1][select[d]];
            auto it = days[select[d]].find(d);
            --it;
            auto pre = *it;
            ++it; ++it;
            auto next = *it;
            sub += ((d-pre)*(d-pre-1)/2 + (next-d)*(next-d-1)/2) * c[select[d]];
            sub -= (next-pre)*(next-pre-1)/2 * c[select[d]];
            q = -1;
            long long sub2 = 0;
            int q2 = xor32()%26;
            while(q2 == select[d]) q2 = xor32()%26;
            for(int j=0;j<26;j++){
                if(j == select[d]) continue;
                it = days[j].lower_bound(d);
                next = *it;
                --it;
                pre = *it;
                long long curSub = s[d-1][j];
                curSub -= ((d-pre)*(d-pre-1)/2 + (next-d)*(next-d-1)/2) * c[j];
                curSub += (next-pre)*(next-pre-1)/2 * c[j];
                if(q == -1 || sub2 < curSub){
                    q = j;
                    sub2 = curSub;
                }
            }
            sub += sub2;
            if(sub > 0 || exp(0.01*sub)/temp > rand()%10000000*1e-7){
                days[select[d]].erase(d);
                days[q].insert(d);
                select[d] = q;
                score += sub;
                if(score > bestScore){
                    bestScore = score;
                    res = select;
                }
            }
        }
    }
    for(int i=1;i<=D;i++) cout << res[i]+1 << endl;
}