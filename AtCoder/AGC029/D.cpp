#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    int H, W, N; cin >> H >> W >> N;
    vector<vector<int>> xs(W+1);
    set<pair<int, int>> S;
    for(int i=0;i<N;i++){
        int X, Y; cin >> X >> Y;
        xs[Y].push_back(X);
        S.emplace(X, Y);
    }
    int x = 1, y = 1;
    int res = H;
    if(!xs[1].empty()) res = *min_element(xs[1].begin(), xs[1].end()) - 1;
    for(int i=1;;i++){
        if(x == H || S.count(make_pair(x+1, y))){
            res = min(i, res);
            break;
        }
        x++;
        if(y < W && !S.count(make_pair(x, y+1))){
            y++;
            for(auto& t : xs[y]) if(x < t) res = min(t-1, res);
        }
    }
    cout << res << endl;
}