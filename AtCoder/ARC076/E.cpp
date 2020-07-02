#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main(){
    int R, C, N; cin >> R >> C >> N;
    auto getIdx = [&](int x, int y){
        if(y == 0) return x;
        if(x == R) return R + y;
        if(y == C) return 2 * R + C - x;
        if(x == 0) return 2 * R + 2 * C - y;
        return -1;
    };
    vector<pair<int, int>> vp;
    for(int i=0;i<N;i++){
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        int idx1 = getIdx(x1, y1);
        int idx2 = getIdx(x2, y2);
        if(idx1 != -1 && idx2 != -1){
            vp.emplace_back(idx1, i);
            vp.emplace_back(idx2, i);
        }
    }
    bool ok = true;
    sort(vp.begin(), vp.end());
    vector<int> check(N, 0);
    stack<int> st;
    for(auto& p : vp){
        int idx = p.second;
        if(check[idx]){
            if(st.top() != idx) ok = false;
            st.pop();
        } else {
            st.push(idx);
            check[idx] = 1;
        }
    }
    cout << (ok ? "YES" : "NO") << endl;
}