#include <iostream>
#include <vector>

using namespace std;

void solve(vector<pair<int,int>>& res, int X, int Y, int K){
    const int sgnX = (X < 0 ? -1 : 1);
    const int sgnY = (Y < 0 ? -1 : 1);
    X *= sgnX; Y *= sgnY;
    bool sw = (Y > X);
    if(sw) swap(X, Y);
    if(K%2 == 0 && (X+Y)%2 == 1) return;
    while(X != 0 || Y != 0){
        if((X+Y)%2 == 0 && X+Y < 2*K && X+Y != K){
            int ax = (X+Y)/2;
            int ay = K - ax;
            int bx = ax;
            int by = -ay;
            ay += Y;
            ax -= Y;
            res.emplace_back(ax, ay);
            res.emplace_back(bx, by);
            break;
        }
        int dy = min(K, Y);
        int dx = K - dy;
        X -= dx; Y -= dy;
        if(X < 0) solve(res, X, Y, K);
        res.emplace_back(dx, dy);
        if(X < 0) break;
    }
    if(sw){
        for(auto& p : res) swap(p.first, p.second);
    }
    for(auto& p : res){
        p.first *= sgnX;
        p.second *= sgnY;
    }
}

int main(){
    int K, X, Y;
    while(cin >> K >> X >> Y){
        vector<pair<int,int>> res;
        solve(res, X, Y, K);
        if(res.empty()){
            cout << -1 << endl;
        } else {
            int x = 0, y = 0;
            cout << res.size() << endl;
            for(auto& p : res){
                x += p.first;
                y += p.second;
                cout << x << " " << y << endl;
            }
        }
    }
}