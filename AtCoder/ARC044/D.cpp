#include <iostream>
#include <vector>

using namespace std;

string solve(const vector<int>& a){
    const int N = a.size();
    vector<int> order(N+1, -1);
    for(int i=0;i<N;i++) order[a[i]] = i;
    string res = string(N, '#');
    int cidx = 0;
    res[a[0]] = 'A' + cidx;
    for(int i=1;i<N;i++){
        if(order[a[i-1]+1] > order[a[i]+1]){
            ++cidx;
            if(cidx == 26) return "-1";
        }
        res[a[i]] = 'A' + cidx;
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> a(N);
        for(auto& t : a) {
            cin >> t;
            --t;
        }
        cout << solve(a) << endl;
    }
}