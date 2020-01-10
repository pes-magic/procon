#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int order(const vector<int>& a){
    vector<int> c(a.size());
    for(int i=0;i<a.size();i++) c[i] = i+1;
    int res = 0;
    do {
        if(c == a) return res;
        ++res;
    } while(next_permutation(c.begin(), c.end()));
    return -1;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> P(N), Q(N);
        for(auto& t : P) cin >> t;
        for(auto& t : Q) cin >> t;
        cout << abs(order(P) - order(Q)) << endl;
    }
}