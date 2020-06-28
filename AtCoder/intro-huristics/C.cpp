#include <iostream>
#include <vector>
#include <set>

using namespace std;

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
        int t; cin >> t;
        --t;
        days[t].insert(i);
        select[i] = t;
        score += s[i-1][t];
        last[t] = i;
        for(int j=0;j<26;j++){
            score -= c[j] * (i - last[j]);
        }
    }
    int M; cin >> M;
    for(int i=0;i<M;i++){
        int d, q; cin >> d >> q;
        --q;
        score -= s[d-1][select[d]];
        score += s[d-1][q];
        auto it = days[select[d]].find(d);
        --it;
        auto pre = *it;
        ++it; ++it;
        auto next = *it;
        score += ((d-pre)*(d-pre-1)/2 + (next-d)*(next-d-1)/2) * c[select[d]];
        score -= (next-pre)*(next-pre-1)/2 * c[select[d]];
        days[select[d]].erase(d);
        it = days[q].lower_bound(d);
        next = *it;
        --it;
        pre = *it;
        score -= ((d-pre)*(d-pre-1)/2 + (next-d)*(next-d-1)/2) * c[q];
        score += (next-pre)*(next-pre-1)/2 * c[q];
        days[q].insert(d);
        select[d] = q;
        cout << score << endl;
    }
}