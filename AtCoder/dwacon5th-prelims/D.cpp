#include <iostream>
#include <vector>

using namespace std;

vector<int> makeSq(int N){
    vector<int> sq(N+1, 0);
    int a = 1, b = 1;
    for(int i=1;i<=N;i++){
        if(a*b < i){
            if(a == b) b++;
            else a++;
        }
        sq[i] = a+b;
    }
    return sq;
}

void makeSum(vector<vector<int>>& v){
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            if(i > 0) v[i][j] += v[i-1][j];
            if(j > 0) v[i][j] += v[i][j-1];
            if(i > 0 && j > 0) v[i][j] -= v[i-1][j-1];
        }
    }
}

int areaSum(int sx, int sy, int ex, int ey, const vector<vector<int>>& v){
    int res = v[ex][ey];
    if(sx > 0) res -= v[sx-1][ey];
    if(sy > 0) res -= v[ex][sy-1];
    if(sx > 0 && sy > 0) res += v[sx-1][sy-1];
    return res;
}

int main(){
    int N, D; cin >> N >> D;
    const auto sq = makeSq(N);
    auto cnt = vector(2*D, vector(2*D, 0));
    auto part = vector(2*D, vector(2*D, 0));
    for(int i=0;i<N;i++){
        int x, y; cin >> x >> y;
        ++cnt[x%D][y%D];
    }
    int mx = 0;
    for(auto& v : cnt){
        for(auto& t : v) { t = sq[t]; mx = max(mx, t); }
    }
    mx = (mx+1)/2*2;
    int num = 0;
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            if(cnt[i][j] == mx) cnt[i][j] = 1;
            else {
                if((cnt[i][j]+1)/2 == (mx+1)/2) part[i][j] = 1;
                cnt[i][j] = 0;
            }
            num += (cnt[i][j] + part[i][j]);
            cnt[i+D][j] = cnt[i+D][j+D] = cnt[i][j+D] = cnt[i][j];
            part[i+D][j] = part[i+D][j+D] = part[i][j+D] = part[i][j];
        }
    }
    makeSum(cnt);
    makeSum(part);
    auto getSum = [&](int x, int y, int d){
        int res = areaSum(x, y, x+d, y+d, cnt);
        res += areaSum(x, y, x+d, y+D-1, part);
        res += areaSum(x, y, x+D-1, y+d, part);
        res -= areaSum(x, y, x+d, y+d, part);
        return res;
    };
    int res = mx * D;
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            int L = -1, R = D-1;
            while(R-L > 1){
                int mid = (L+R)/2;
                if(getSum(i, j, mid) >= num) R = mid;
                else L = mid;
            }
            res = min(res, ((mx+1)/2-1)*D+R);
        }
    }
    cout << res << endl;
}