#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    map<int, int> row;
    map<int, vector<int>> col;
    int N; cin >> N;
    for(int i=0;i<N;i++){
        int x, y; cin >> x >> y;
        if(!row.count(y)) row[y] = 0;
        row[y] = 1 - row[y];
        if(!col.count(x)) col[x] = vector<int>(3, 0);
        col[x][y%3] = 1 - col[x][y%3];
    }
    vector<int> rs(3, 0);
    for(auto& p : row){
        rs[p.first%3] += p.second%2;
    }
    vector<int> num(3, 0);
    for(auto& p : col){
        int m = 2*(2*p.second[2] + p.second[1]) + p.second[0];
        if(m%7 == 0) continue;
        num[min(m, 7-m)-1]++;
    }
    int ofs = (rs[0]%2 != num[0]%2 ? 1 : 0);
    int res = max(rs[0], num[0]+ofs) + max(rs[1], num[1]+ofs) + max(rs[2], num[2]+ofs);
    for(int i=ofs;i<=num[0];i+=2){
        res = min(res, max(rs[0], num[0]-i) + max(rs[1], num[1]+i) + max(rs[2], num[2]+i));
    }
    for(int i=ofs;i<=num[1];i+=2){
        res = min(res, max(rs[0], num[0]+i) + max(rs[1], num[1]-i) + max(rs[2], num[2]+i));
    }
    for(int i=ofs;i<=num[2];i+=2){
        res = min(res, max(rs[0], num[0]+i) + max(rs[1], num[1]+i) + max(rs[2], num[2]-i));
    }
    cout << res << endl;
}