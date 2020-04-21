#include <iostream>
#include <vector>

using namespace std;

string query(int x, int y){
    cout << x << " " << y << endl;
    string res; cin >> res;
    return res;
}

void solve(){
    int sx, sy;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    for(int d=0;d<4;d++){
        int x = dx[d] * 500000000;
        int y = dy[d] * 500000000;
        auto s = query(x, y);
        if(s == "MISS") continue;
        if(s == "CENTER") return;
        sx = x;
        sy = y;
        break;
    }
    int resX, resY;
    {
        int l = -1000000001, r = sx;
        while(r-l > 1){
            int mid = (l+r)/2;
            auto s = query(mid, sy);
            if(s == "CENTER") return;
            if(s == "MISS") l = mid;
            else r = mid;
        }
        int left = r;
        l = sx, r = 1000000001;
        while(r-l > 1){
            int mid = (l+r)/2;
            auto s = query(mid, sy);
            if(s == "CENTER") return;
            if(s == "MISS") r = mid;
            else l = mid;
        }
        resX = (l+left)/2;
    }
    {
        int l = -1000000001, r = sy;
        while(r-l > 1){
            int mid = (l+r)/2;
            auto s = query(sx, mid);
            if(s == "CENTER") return;
            if(s == "MISS") l = mid;
            else r = mid;
        }
        int left = r;
        l = sy, r = 1000000001;
        while(r-l > 1){
            int mid = (l+r)/2;
            auto s = query(sx, mid);
            if(s == "CENTER") return;
            if(s == "MISS") r = mid;
            else l = mid;
        }
        resY = (l+left)/2;
    }
    query(resX, resY);
}

int main(){
    int T, A, B; cin >> T >> A >> B;
    for(int t=0;t<T;t++) solve();
}