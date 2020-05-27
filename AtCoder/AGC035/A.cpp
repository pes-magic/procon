#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(const vector<int>& a){
    if(all_of(a.begin(), a.end(), [](int t){ return t==0; })) return true;
    if(a.size()%3 != 0) return false;
    int d = a.size()/3;
    for(int i=0;i<a.size();i++){
        if(a[i] != a[i/d*d]) return false;
    }
    return (a[0]^a[d]) == a[2*d];
}

int main(){
    int N; cin >> N;
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    sort(a.begin(), a.end());
    cout << (check(a) ? "Yes" : "No") << endl;
}