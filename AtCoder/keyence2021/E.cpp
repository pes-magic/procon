#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int mem[402][402][402];

int search(const vector<int>& a, int left, int right, int s){
    int n = a.size();
    if(left == 0 && right == n-1) return 0;
    if(mem[left][right][s] >= 0) return mem[left][right][s];
    int res = 0;
    if(a[left] > 0 && s > 0) res = max(res, search(a, left-1, right, s-1) + a[left]);
    if(a[right] > 0 && s > 0) res = max(res, search(a, left, right+1, s-1) + a[right]);
    if(a[left] > a[right]){
        res = max(res, search(a, left-1, right, s+1));
    } else {
        res = max(res, search(a, left, right+1, s+1));
    }
    return mem[left][right][s] = res;
};

int main(){
    int N; cin >> N;
    memset(mem, -1, sizeof(mem));
    vector<int> a(N+2, 0);
    for(int i=1;i<=N;i++) cin >> a[i];
    for(int i=1;i<=N+1;i++) cout << search(a, i-1, i, 1) << endl;
}