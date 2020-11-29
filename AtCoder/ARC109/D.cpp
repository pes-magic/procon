#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

using Node = pair<pair<int, int>, int>;

vector<pair<Node, int>> search(int sx, int sy, int sp){
    map<Node, int> mp;
    vector<pair<Node, int>> res;
    Node start = make_pair(make_pair(sx, sy), sp);
    mp[start] = 0;
    res.emplace_back(start, 0);
    queue<Node> qu;
    qu.push(start);
    while(!qu.empty()){
        auto nd = qu.front(); qu.pop();
        if(mp[nd] == 3) break;
        int cur = mp[nd];
        auto next = nd;
        for(int i=0;i<4;i++){
            next.second = i;
            if(!mp.count(next)){
                mp[next] = cur + 1;
                res.emplace_back(next, cur+1);
                qu.push(next);
            }
        }
        if(nd.second%2 == 1){
            next = nd;
            --next.first.first;
            for(int i=0;i<4;i+=2){
                next.second = i;
                if(!mp.count(next)){
                    mp[next] = cur + 1;
                    res.emplace_back(next, cur+1);
                    qu.push(next);
                }
            }
        }
        if(nd.second%2 == 0){
            next = nd;
            ++next.first.first;
            for(int i=1;i<4;i+=2){
                next.second = i;
                if(!mp.count(next)){
                    mp[next] = cur + 1;
                    res.emplace_back(next, cur+1);
                    qu.push(next);
                }
            }
        }
        if(nd.second < 2){
            next = nd;
            --next.first.second;
            for(int i=2;i<4;i++){
                next.second = i;
                if(!mp.count(next)){
                    mp[next] = cur + 1;
                    res.emplace_back(next, cur+1);
                    qu.push(next);
                }
            }
        }
        if(nd.second >= 2){
            next = nd;
            ++next.first.second;
            for(int i=0;i<2;i++){
                next.second = i;
                if(!mp.count(next)){
                    mp[next] = cur + 1;
                    res.emplace_back(next, cur+1);
                    qu.push(next);
                }
            }
        }
    }
    return res;
}

int main(){
    auto src = search(0, 0, 1);
    int T; cin >> T;
    for(int t=0;t<T;t++){
        int ax, ay, bx, by, cx, cy; cin >> ax >> ay >> bx >> by >> cx >> cy;
        int xmin = min(ax, min(bx, cx));
        int ymin = min(ay, min(by, cy));
        int b = 0;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                if(xmin+j == ax && ymin+i == ay) continue;
                if(xmin+j == bx && ymin+i == by) continue;
                if(xmin+j == cx && ymin+i == cy) continue;
                b = 2*(1-i)+j;
            }
        }
        auto dst = search(xmin, ymin, b);
        long long res = (1LL << 60);
        for(auto& a : src){
            for(auto& b : dst){
                if(a.first.second != b.first.second) continue;
                long long dx = b.first.first.first - a.first.first.first;
                long long dy = b.first.first.second - a.first.first.second;
                long long step = a.second + b.second;
                if(a.first.second == 1 || a.first.second == 2){
                    if(dx*dy > 0){
                        dx = abs(dx);
                        dy = abs(dy);
                        auto m = min(dx, dy);
                        step += 3 * m;
                        dx -= m;
                        dy -= m;
                        step += 2 * (dx + dy);
                    } else {
                        step += 2 * max(abs(dx), abs(dy));
                    }
                } else {
                    if(dx*dy < 0){
                        dx = abs(dx);
                        dy = abs(dy);
                        auto m = min(dx, dy);
                        step += 3 * m;
                        dx -= m;
                        dy -= m;
                        step += 2 * (dx + dy);
                    } else {
                        step += 2 * max(abs(dx), abs(dy));
                    }
                }
                res = min(res, step);
            }
        }
        cout << res << endl;
    }
}