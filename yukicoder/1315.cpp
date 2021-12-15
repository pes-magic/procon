#include <iostream>
#include <string>

using namespace std;

int getValue(int x, int y){
    int v = max(abs(x), abs(y));
    if(v == 0) return 1;
    int base = (2*v+1) * (2*v+1);
    if(y == -v) return base - (v-x);
    base -= 2*v;
    if(x == -v) return base - (v+y);
    base -= 2*v;
    if(y == v) return base - (v+x);
    base -= 2*v;
    return base - (v-y);
}

pair<int, int> pos(int v){
    if(v == 1) return make_pair(0, 0);
    int b = 0;
    while((2*b+1)*(2*b+1) < v) b++;
    v -= (2*b-1)*(2*b-1) + 1;
    int x = b, y = -b+1;
    if(v < 2*b) return make_pair(b, -b+1+v);
    v -= 2*b;
    if(v < 2*b) return make_pair(b-1-v, b);
    v -= 2*b;
    if(v < 2*b) return make_pair(-b, b-1-v);
    v -= 2*b;
    return make_pair(-b+1+v, -b);
}

pair<string, int> getPath(int sx, int sy, int gx, int gy){
    string res = "";
    int val = 0;
    int x = sx, y = sy;
    while(x != gx){
        val ^= getValue(x, y);
        if(x < gx){
            res += 'R';
            x++;
        } else {
            res += 'L';
            x--;
        }
    }
    while(y != gy){
        val ^= getValue(x, y);
        if(y < gy){
            res += 'U';
            y++;
        } else {
            res += 'D';
            y--;
        }
    }
    return make_pair(res, val);
}

int main(){
    int S, T; cin >> S >> T;
    auto [sx, sy] = pos(S);
    auto [gx, gy] = pos(T);
    auto [res, val] = getPath(sx, sy, gx, gy);
    if(val == 0){
        res += "LRUD";
        val ^= getValue(gx-1, gy);
        val ^= getValue(gx, gy+1);
    }
    auto [px, py] = pos(val);
    auto m = getPath(gx, gy, px, py).first;
    res += m;
    for(int i=m.size()-1;i>=0;i--){
        if(m[i] == 'L') res += 'R';
        if(m[i] == 'R') res += 'L';
        if(m[i] == 'U') res += 'D';
        if(m[i] == 'D') res += 'U';
    }
    cout << 0 << endl;
    cout << res.size() << endl;
    cout << res << endl;
}