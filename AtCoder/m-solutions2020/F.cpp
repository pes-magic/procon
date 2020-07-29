#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1 << 30;

int solve(const vector<int>& x, const vector<int>& y, const vector<char>& u, char s, char t, auto f, auto g){
    const int N = x.size();
    int res = INF;
    vector<vector<pair<int, char>>> vv(400001);
    for(int i=0;i<N;i++){
        if(u[i] != s && u[i] != t) continue;
        vv[f(x[i], y[i])].emplace_back(g(x[i], y[i]), u[i]);
    }
    for(auto& v : vv){
        if(v.size() < 2) continue;
        sort(v.begin(), v.end());
        for(int i=0;i+1<v.size();i++){
            if(v[i].second == s && v[i+1].second == t){
                res = min(res, 5 * (v[i+1].first - v[i].first));
            }
        }
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<int> X(N), Y(N);
    vector<char> U(N);
    for(int i=0;i<N;i++) cin >> X[i] >> Y[i] >> U[i];
    auto x = [](int a, int b){ return a; };
    auto y = [](int a, int b){ return b; };
    auto add = [](int a, int b){ return a+b; };
    auto sub = [](int a, int b){ return a-b+200000; };
    int res = INF;
    res = min(res, solve(X, Y, U, 'R', 'L', y, x));
    res = min(res, solve(X, Y, U, 'U', 'D', x, y));
    res = min(res, solve(X, Y, U, 'R', 'D', sub, add));
    res = min(res, solve(X, Y, U, 'U', 'L', sub, add));
    res = min(res, solve(X, Y, U, 'R', 'U', add, sub));
    res = min(res, solve(X, Y, U, 'D', 'L', add, sub));
    if(res < INF){
        cout << res << endl;
    } else {
        cout << "SAFE" << endl;
    }
}