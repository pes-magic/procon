#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(){
    int N; cin >> N;
    vector<int> used(200, 0);
    vector<int> own;
    long long sumA = 0, sumB = 0;
    vector<int> valA;
    vector<int> valB;
    for(int i=0;i<30;i++){
        if((1<<i) < 200) used[1<<i] = 1;
        own.push_back(1 << i);
    }
    for(int k=1;k<200;k++){
        if(used[k]) continue;
        own.push_back(k);
        if(own.size() == 100) break;
    }
    sort(own.rbegin(), own.rend());
    cout << own[0];
    for(int i=1;i<100;i++) cout << " " << own[i];
    cout << endl;
    for(int i=0;i<100;i++){
        int v; cin >> v;
        if(sumA < sumB){
            sumA += v;
            valA.push_back(v);
        } else {
            sumB += v;
            valB.push_back(v);
        }
    }
    for(auto& v : own){
        if(sumA < sumB){
            sumA += v;
            valA.push_back(v);
        } else {
            sumB += v;
            valB.push_back(v);
        }
    }
    cout << valA[0];
    for(int i=1;i<valA.size();i++) cout << " " << valA[i];
    cout << endl;
}

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        solve();
    }
}