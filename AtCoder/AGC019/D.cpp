#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int solve(const string& A, const string& B){
    const int N = A.size();
    int s = B.find('1');
    if(s == string::npos) return (A.find('1') == string::npos ? 0 : -1);
    vector<int> nextL(N), nextR(N);
    int p = 0;
    for(int i=0;i<N;i++){
        if(B[(s+i)%N] == '1') p = (s+i)%N;
        nextL[(s+i)%N] = p;
    }
    for(int i=0;i<N;i++){
        if(B[(s+N-i)%N] == '1') p = (s+N-i)%N;
        nextR[(s+N-i)%N] = p;
    }
    int res = 10 * N;
    for(int shift=0;shift<N;shift++){
        int cur = 0;
        vector<pair<int, int>> vp;
        for(int i=0;i<N;i++){
            if(A[i] == B[(i+shift)%N]) continue;
            ++cur;
            if(A[i] == '0') continue;
            if(i+shift < N && i <= nextR[i] && nextR[i] <= i+shift) continue;
            if(i+shift >= N && (nextR[i] <= (i+shift)%N || i <= nextR[i])) continue;
            int left = nextL[i] - i;
            if(left > 0) left -= N;
            int right = nextR[(i+shift)%N] - (i+shift)%N;
            if(right < 0) right += N;
            vp.emplace_back(left, right);
        }
        sort(vp.begin(), vp.end());
        int addMove = 3*N;
        int maxR = 0;
        for(auto& v : vp){
            addMove = min(addMove, -v.first + maxR);
            maxR = max(maxR, v.second);
        }
        addMove = min(addMove, maxR);
        res = min(res, cur + shift + 2 * addMove);
    }
    return res;
}

int main(){
    string A, B;
    while(cin >> A >> B){
        int a = solve(A, B);
        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());
        int b = solve(A, B);
        cout << min(a, b) << endl;
    }
}