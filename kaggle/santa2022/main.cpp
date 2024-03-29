#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string>
#include <vector>
#include "mincostflow.hpp" // acl

using namespace std;

struct P2 {
    int x, y;
    explicit P2(int x=0, int y=0) : x(x), y(y){}
    bool operator < (const P2& p) const { return x != p.x ? x < p.x : y < p.y; }
    bool operator == (const P2& p) const { return x == p.x && y == p.y; }
};

using Arms = vector<P2>;
using Solution = vector<Arms>;

struct Pixel {
    double r, g, b;
};

using Image = array<array<Pixel, 257>, 257>;

class XorShift {
public:
    using result_type = uint32_t;
    explicit XorShift(result_type seed){ init(seed); }
    void init(result_type s){
        x = 1812433253U * (s ^ (s >> 30));
        y = 1812433253U * (x ^ (x >> 30)) + 1;
        z = 1812433253U * (y ^ (y >> 30)) + 2;
        w = 1812433253U * (z ^ (z >> 30)) + 3;
    }
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    result_type operator() () {
        result_type t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
private:
    result_type x;
    result_type y;
    result_type z;
    result_type w;
};

class UnionFind {
public:
    explicit UnionFind(int N) : root(N, -1), size(N, 1) {}
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    int getSize(int u){ return size[getRoot(u)]; }
    bool same(int a, int b){
        return getRoot(a) == getRoot(b);
    }
    bool merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u == v) return false;
        root[u] = v;
        size[v] += size[u];
        return true;
    }
private:
    vector<int> root;
    vector<int> size;
};

unsigned int randomValue(){
    static random_device random;
    return random();
}

class Timer {
public:
    explicit Timer()
        : mStart(chrono::system_clock::now())
    {}
    void start() { mStart = chrono::system_clock::now(); }
    double msec() const {
        auto t = chrono::system_clock::now();
        return 1e-3 * chrono::duration_cast<std::chrono::microseconds>(t - mStart).count();
    }
private:
    chrono::system_clock::time_point mStart;
};

Image loadImage(const string& path){
    ifstream ifs(path);
    Image res;
    int cnt = 0;
    string S; ifs >> S;
    while(ifs >> S){
        int x, y;
        double r, g, b;
        int va = sscanf(S.c_str(), "%d,%d,%lf,%lf,%lf", &x, &y, &r, &g, &b);
        res[x+128][y+128].r = r;
        res[x+128][y+128].g = g;
        res[x+128][y+128].b = b;
        ++cnt;
    }
    if(cnt != 257*257) cerr << "Given image is not valid" << endl;
    return res;
}

bool validateArm(const Arms& arms){
    if(arms.size() != 8) return false;
    int size = 64;
    for(auto& a : arms){
        if(max(abs(a.x), abs(a.y)) != size) return false;
        size = max(1, size/2);
    }
    return true;
}

bool isInitialArm(const Arms& arms){
    int size = 64;
    bool first = true;
    for(auto& a : arms){
        if(first){
            if(a.x != size) return false;
            first = false;
        } else {
            if(a.x != -size) return false;
        }
        if(a.y != 0) return false;
        size = max(1, size/2);
    }
    return true;
}

bool validateSolution(const Solution& solution){
    vector<vector<int>> visit(257, vector<int>(257, 0));
    int cnt = 0;
    const int n = solution.size();
    if(solution.empty()){
        cerr << "Solution should not be empty" << endl;
        return false;
    }
    if(!isInitialArm(solution.front())){
        cerr << "Initial state is not valid" << endl;
        return false;
    }
    if(!isInitialArm(solution.back())){
        cerr << "Final state is not valid" << endl;
        return false;
    }
    for(int i=0;i<n;i++){
        if(!validateArm(solution[i])){
            cerr << "Arm " << i << " is invalid" << endl;
            return false;
        }
        if(i+1 < n){
            const auto& cur = solution[i];
            const auto& next = solution[i+1];
            if(cur.size() != next.size()){
                cerr << "Size of Arm " << i << " and Arm " << i+1 << " are different" << endl;
                return false;
            }
            for(int j=0;j<(int)cur.size();j++){
                const int m = abs(cur[j].x - next[j].x) + abs(cur[j].y - next[j].y);
                if(m >= 2){
                    cerr << "Invalid move on " << i << endl;
                    return false;
                }
            }
        }
        int x = 128, y = 128;
        for(auto& a : solution[i]){
            x += a.x;
            y += a.y;
        }
        if(!visit[x][y]){
            ++cnt;
            visit[x][y] = 1;
        } else if(i!= n-1 || x != 128 || y != 128){
            cerr << "Invalid move on " << i << " " << x << " " << y << endl;
        }
    }
    if(cnt != 257*257){
        cerr << "Some pixels are not painted" << endl;
        return false;
    }
    return true;
}

Solution loadSolution(const std::string& path){
    Solution res;
    std::string S;
    int v;
    ifstream ifs(path);
    ifs >> S;
    while(ifs >> v){
        Arms vp;
        for(int i=0;i<7;i++){
            ifs >> S;
            int a, b;
            sscanf(S.c_str(), "%d;%d", &a, &b);
            vp.emplace_back(v, a);
            v = b;
        }
        int b; ifs >> b;
        vp.emplace_back(v, b);
        res.emplace_back(move(vp));
    }
    return res;
}

void printSolution(const Solution& solution, const string& path){
    if(!validateSolution(solution)){
        cerr << "solution output to " << path << " is not valid" << endl;
    }
    ofstream ofs(path);
    ofs << "configuration" << endl;
    for(auto& arms : solution){
        bool first = true;
        for(auto& a : arms){
            if(first){
                first = false;
            } else {
                ofs << ";";
            }
            ofs << a.x << " " << a.y;
        }
        ofs << endl;
    }
}

double calcScore(const Solution& solution, const Image& image){
    double res = 0.0;
    const int n = solution.size();
    if(n == 0) return 1e12;
    int curX = 128, curY = 128;
    for(auto& a : solution.front()){
        curX += a.x;
        curY += a.y;
    }
    for(int i=0;i+1<n;i++){
        int nextX = 128, nextY = 128;
        for(auto& a : solution[i+1]){
            nextX += a.x;
            nextY += a.y;
        }
        int moveCost = 0;
        for(int j=0;j<(int)solution[i].size();j++){
            moveCost += abs(solution[i][j].x - solution[i+1][j].x);
            moveCost += abs(solution[i][j].y - solution[i+1][j].y);
        }
        double colorCost = 0;
        colorCost += abs(image[curX][curY].r - image[nextX][nextY].r);
        colorCost += abs(image[curX][curY].g - image[nextX][nextY].g);
        colorCost += abs(image[curX][curY].b - image[nextX][nextY].b);
        res += sqrt(moveCost) + 3.0 * colorCost;
        curX = nextX;
        curY = nextY;
    }
    return res;
}

P2 getPosition(const Arms& arms){
    P2 p;
    for(auto& a : arms){
        p.x += a.x;
        p.y += a.y;
    }
    return p;
}

vector<P2> createSimpleRoute1(){
    vector<P2> res;
    int x = 64, y = 1;
    while(true){
        while(true){
            res.emplace_back(x, y);
            if(y == 63) break;
            ++y;
        }
        if(x == -64) break;
        --x;
        while(true){
            res.emplace_back(x, y);
            if(y == -64) break;
            --y;
        }
        --x;
    }
    return res;
}

vector<P2> createSimpleRoute2(){
    vector<P2> res;
    int x = -63, y = 64;
    while(true){
        while(true){
            res.emplace_back(x, y);
            if(x == 64) break;
            ++x;
        }
        if(y == -64) break;
        --y;
        while(true){
            res.emplace_back(x, y);
            if(x == -63) break;
            --x;
        }
        --y;
    }
    res.pop_back(); // remove the last point which overlap with changing quadrant
    return res;
}

vector<P2> createSimpleRoute3(){
    vector<P2> res;
    for(int y=-64;y<=63;y++) res.emplace_back(63, y);
    for(int y=63;y-1>=0;y-=2){
        for(int x=62;x>=-63;x--) res.emplace_back(x, y);
        for(int x=-63;x<=62;x++) res.emplace_back(x, y-1);
    }
    for(int x=62;x-1>=-63;x-=2){
        for(int y=-1;y>=-64;y--) res.emplace_back(x, y);
        for(int y=-64;y<=-1;y++) res.emplace_back(x-1, y);
    }
    for(int y=-1;y>=-63;y--) res.emplace_back(-64, y);
    return res;
}

vector<P2> createSimpleRoute4(){
    vector<P2> res;
    for(int y=-63;y+1<=0;y+=2){
        for(int x=-64;x<=63;x++) res.emplace_back(x, y);
        for(int x=63;x>=-64;x--) res.emplace_back(x, y+1);
    }
    for(int x=-64;x+1<=63;x+=2){
        for(int y=1;y<=63;y++) res.emplace_back(x, y);
        for(int y=63;y>=1;y--) res.emplace_back(x+1, y);
    }
    return res;
}

vector<pair<P2, P2>> simpleRouteP2(){
    vector<pair<P2, P2>> route;
    for(int i=0;i<=64;i++){
        route.push_back(make_pair(P2(64, i), P2(-64, 0)));
    }
    {
        auto r1 = createSimpleRoute1();
        for(auto& p : r1){
            route.push_back(make_pair(P2(p.x, 64), P2(-64, p.y)));
        }
    }
    for(int i=-64;i<=64;i++) route.push_back(make_pair(P2(-64, 64), P2(i, 64)));
    {
        auto r2 = createSimpleRoute2();
        for(auto& p : r2){
            route.push_back(make_pair(P2(p.x, 64), P2(64, p.y)));
        }
    }
    for(int i=64;i>=-64;i--) route.push_back(make_pair(P2(64, i), P2(64, -64)));
    {
        auto r3 = createSimpleRoute3();
        for(auto& p : r3){
            route.push_back(make_pair(P2(p.x, -64), P2(64, p.y)));
        }
    }
    for(int i=64;i>=-64;i--) route.push_back(make_pair(P2(-64, -64), P2(i, -64)));
    {
        auto r4 = createSimpleRoute4();
        for(auto& p : r4){
            route.push_back(make_pair(P2(p.x, -64), P2(-64, p.y)));
        }
    }
    for(int i=-64;i<=0;i++) route.push_back(make_pair(P2(64, i), P2(-64, 0)));
    return route;
}

vector<P2> outputTSPfileForLKH(const vector<P2>& current, const Image& image, const P2& offset){
    auto colorCost = [&](int x1, int y1, int x2, int y2){
        const auto& p1 = image[offset.x + x1][offset.y + y1];
        const auto& p2 = image[offset.x + x2][offset.y + y2];
        double res = 0.0;
        res += abs(p1.r - p2.r);
        res += abs(p1.g - p2.g);
        res += abs(p1.b - p2.b);
        return 3*res;
    };

    string basename = to_string(offset.x) + "_" + to_string(offset.y) + "_tour";
    ofstream tsp(basename + ".tsp");
    ofstream tour(basename + ".init");

    const double diagMove = (sqrt(2.0)-1);

    const int INF = 100000000;

    tsp << "NAME: santa" << endl;
    tsp << "TYPE: TSP" << endl;
    tsp << "COMMENT: santa " << offset.x << " " << offset.y << endl;
    tsp << "DIMENSION: " << current.size()+1 << endl;
    tsp << "EDGE_WEIGHT_TYPE: EXPLICIT" << endl;
    tsp << "EDGE_WEIGHT_FORMAT: UPPER_ROW" << endl;
    tsp << "EDGE_WEIGHT_SECTION" << endl;

    int curBest = 0;

    for(int i=0;i<=current.size();i++){
        for(int j=i+1;j<=current.size();j++){
            const auto& p1 = current[i];
            const auto& p2 = current[j];
            if(j == current.size()){
                tsp << ((i == 0 || i+1 == current.size()) ? 0 : INF) << endl;
            } else {
                int dx = abs(p1.x - p2.x);
                int dy = abs(p1.y - p2.y);
                if(dx >= 2 || dy >= 2){
                    tsp << INF << " ";
                    if(j==i+1) cerr << "ERROR" << endl;
                } else {
                    double cost = colorCost(p1.x, p1.y, p2.x, p2.y) + (dx == 1 && dy == 1 ? diagMove : 0);
                    int icost = int(10000*cost);
                    tsp << icost << " ";
                    if(j==i+1) curBest += icost;
                }
            }
        }
    }
    tsp << "EOF" << endl;

    tour << "NAME : " << basename << ".init" << endl;
    tour << "TYPE : TOUR" << endl;
    tour << "DIMENSION: " << current.size()+1 << endl;
    tour << "TOUR_SECTION" << endl;
    for(int i=1;i<=current.size()+1;i++) tour << i << endl;
    tour << -1 << endl;
    tour << "EOF" << endl;
    cerr << "CurCost: " << curBest << endl;
    return current;
}

vector<P2> optimizeByLKH(const vector<P2>& current, const Image& image, const P2& offset){
    // apply solution found by LKH
    string filename = to_string(offset.x) + "_" + to_string(offset.y) + ".tour";
    ifstream ifs(filename);
    string s = "";
    while(s != "TOUR_SECTION"){
        ifs >> s;
        if(ifs.fail()) break;
    }
    if(ifs.fail()){
        cerr << "tour file is not found or invalid" << endl;
        return current;
    }
    vector<P2> res(current.size());
    for(auto& p : res){
        int idx; ifs >> idx;
        --idx;
        p = current[idx];
    }
    return res;
}

vector<P2> optimizeByMCF(const vector<P2>& current, const Image& image, const P2& offset){
    vector<vector<double>> cost(257, vector<double>(257, 0));

    auto colorCost = [&](int x1, int y1, int x2, int y2){
        const auto& p1 = image[offset.x + x1][offset.y + y1];
        const auto& p2 = image[offset.x + x2][offset.y + y2];
        double res = 0.0;
        res += abs(p1.r - p2.r);
        res += abs(p1.g - p2.g);
        res += abs(p1.b - p2.b);
        return res;
    };

    for(int x=-64;x<=64;x++){
        for(int y=-64;y<=64;y++){
            if(x+1 <= 64) cost[2*x+129][2*y+128] = colorCost(x, y, x+1, y);
            if(y+1 <= 64) cost[2*x+128][2*y+129] = colorCost(x, y, x, y+1);
        }
    }

    double currentCost = 0.0;
    vector<vector<int>> path(258, vector<int>(258, 0));
    for(auto& p : current) path[2*p.x+128][2*p.y+128] = 1;
    path[2*current.front().x+128][2*current.front().y+128] = 2;
    path[2*current.back().x+128][2*current.back().y+128] = 2;

    for(size_t i=0;i+1<current.size();i++){
        const int px = 2*current[i].x + 128;
        const int py = 2*current[i].y + 128;
        const int nx = 2*current[i+1].x + 128;
        const int ny = 2*current[i+1].y + 128;
        const int mx = (px+nx)/2;
        const int my = (py+ny)/2;
        // path[mx][my] = 1;
        currentCost += cost[mx][my];
    }
    cerr << "CurrentCost: " << currentCost << endl;
    atcoder::mcf_graph<int, double> mcf(129*129+2);

    const int startNode = 129*129;
    const int endNode = 129*129+1;

    for(int x=0;x<=128;x++){
        for(int y=0;y<=128;y++){
            if((x+y)%2){
                mcf.add_edge(129*x+y, endNode, 3 - path[2*x][2*y], 0.0);
            } else {
                mcf.add_edge(startNode, 129*x+y, 3 - path[2*x][2*y], 0.0);
            }
            if(2*y+2 <= 256 && path[2*x][2*y] && path[2*x][2*y+2]){
                if((x+y)%2){
                    mcf.add_edge(129*x+y+1, 129*x+y, 1, cost[2*x][2*y+1]);
                } else {
                    mcf.add_edge(129*x+y, 129*x+y+1, 1, cost[2*x][2*y+1]);
                }
            }
            if(2*x+2 <= 256 && path[2*x][2*y] && path[2*x+2][2*y]){
                if((x+y)%2){
                    mcf.add_edge(129*x+y+129, 129*x+y, 1, cost[2*x+1][2*y]);
                } else {
                    mcf.add_edge(129*x+y, 129*x+y+129, 1, cost[2*x+1][2*y]);
                }
            }
        }
    }

    Timer timer;
    auto mcfResult = mcf.flow(startNode, endNode);
    cerr << "Flow: " << timer.msec() << " " << mcfResult.first << " " << mcfResult.second << " " << current.size() << endl;
    for(const auto& e : mcf.edges()){
        if(e.from == startNode) continue;
        if(e.to == endNode) continue;
        if(e.flow == 0) continue;
        int x1 = e.from/129 * 2;
        int y1 = e.from%129 * 2;
        int x2 = e.to/129 * 2;
        int y2 = e.to%129 * 2;
        path[(x1+x2)/2][(y1+y2)/2] = 1;
    }
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, -1, 0, 1};

    int curGroup = current.size();
    double addCost = 0.0;

    vector<vector<P2>> warp(257, vector<P2>(257, P2(-1, -1)));

    {
        vector<vector<int>> visit(257, vector<int>(257, -1));
        int group = 0;
        for(int i=0;i<=256;i++){
            for(int j=0;j<=256;j++){
                if(path[i][j] == 0) continue;
                if(visit[i][j] != -1) continue;
                queue<pair<int, int>> qu;
                qu.emplace(i, j);
                visit[i][j] = group;
                while(!qu.empty()){
                    auto pr = qu.front(); qu.pop();
                    const int cx = pr.first;
                    const int cy = pr.second;
                    for(int k=0;k<4;k++){
                        const int nx = cx + dx[k];
                        if(nx < 0 || 256 < nx) continue;
                        const int ny = cy + dy[k];
                        if(ny < 0 || 256 < ny) continue;
                        if(!path[nx][ny] || visit[nx][ny] != -1) continue;
                        visit[nx][ny] = group;
                        qu.emplace(nx, ny);
                    }
                }
                ++group;
            }
        }
        vector<pair<pair<double, vector<P2>>, pair<int, int>>> edges;
        const double diagMove = (sqrt(2.0)-1.0)/3.0;
        for(int x=1;x<=255;x+=2){
            for(int y=1;y<=255;y+=2){
                if(path[x-1][y]){
                    if(path[x+1][y]){
                        if(visit[x-1][y] == visit[x+1][y]) continue;
                        double c = cost[x][y-1] + cost[x][y+1] - cost[x-1][y] - cost[x+1][y];
                        vector<P2> ps;
                        ps.emplace_back(x-1, y-1);
                        ps.emplace_back(x-1, y+1);
                        ps.emplace_back(x+1, y-1);
                        ps.emplace_back(x+1, y+1);
                        edges.emplace_back(make_pair(c, ps), make_pair(visit[x-1][y], visit[x+1][y]));
                    }
                    const int bx = (x-1)/2 - 64;
                    const int by = (y-1)/2 - 64;
                    if(y-2 >= 1 && path[x+1][y-2]){
                        if(visit[x-1][y] == visit[x+1][y-2]) continue;
                        double c = diagMove + colorCost(bx, by, bx+1, by-1) + colorCost(bx, by+1, bx+1, by) - cost[x-1][y] - cost[x+1][y-2];
                        vector<P2> ps;
                        ps.emplace_back(x-1, y-1);
                        ps.emplace_back(x-1, y+1);
                        ps.emplace_back(x+1, y-3);
                        ps.emplace_back(x+1, y-1);
                        edges.emplace_back(make_pair(c, ps), make_pair(visit[x-1][y], visit[x+1][y-2]));
                    }
                    if(y+2 <= 255 && path[x+1][y+2]){
                        if(visit[x-1][y] == visit[x+1][y+2]) continue;
                        double c = diagMove + colorCost(bx, by, bx+1, by+1) + colorCost(bx, by+1, bx+1, by+2) - cost[x-1][y] - cost[x+1][y+2];
                        vector<P2> ps;
                        ps.emplace_back(x-1, y-1);
                        ps.emplace_back(x-1, y+1);
                        ps.emplace_back(x+1, y+1);
                        ps.emplace_back(x+1, y+3);
                        edges.emplace_back(make_pair(c, ps), make_pair(visit[x-1][y], visit[x+1][y+2]));
                    }
                }
                if(path[x][y-1]){
                    if(path[x][y+1]){
                        if(visit[x][y-1] == visit[x][y+1]) continue;
                        double c = cost[x-1][y] + cost[x+1][y] - cost[x][y-1] - cost[x][y+1];
                        vector<P2> ps;
                        ps.emplace_back(x-1, y-1);
                        ps.emplace_back(x+1, y-1);
                        ps.emplace_back(x-1, y+1);
                        ps.emplace_back(x+1, y+1);
                        edges.emplace_back(make_pair(c, ps), make_pair(visit[x][y-1], visit[x][y+1]));
                    }
                    const int bx = (x-1)/2 - 64;
                    const int by = (y-1)/2 - 64;
                    if(x-2 >= 1 && path[x-2][y+1]){
                        if(visit[x][y-1] == visit[x-2][y+1]) continue;
                        double c = diagMove + colorCost(bx, by, bx-1, by+1) + colorCost(bx+1, by, bx, by+1) - cost[x][y-1] - cost[x-2][y+1];
                        vector<P2> ps;
                        ps.emplace_back(x-1, y-1);
                        ps.emplace_back(x+1, y-1);
                        ps.emplace_back(x-3, y+1);
                        ps.emplace_back(x-1, y+1);
                        edges.emplace_back(make_pair(c, ps), make_pair(visit[x][y-1], visit[x-2][y+1]));
                    }
                    if(x+2 <= 255 && path[x+2][y+1]){
                        if(visit[x][y-1] == visit[x+2][y+1]) continue;
                        double c = diagMove + colorCost(bx, by, bx+1, by+1) + colorCost(bx+1, by, bx+2, by+1) - cost[x][y-1] - cost[x+2][y+1];
                        vector<P2> ps;
                        ps.emplace_back(x-1, y-1);
                        ps.emplace_back(x+1, y-1);
                        ps.emplace_back(x+1, y+1);
                        ps.emplace_back(x+3, y+1);
                        edges.emplace_back(make_pair(c, ps), make_pair(visit[x][y-1], visit[x+2][y+1]));
                    }
                }
            }
        }
        sort(edges.begin(), edges.end());
        UnionFind uf(group);
        for(auto& e : edges){
            // cerr << e.second.first<< " " << e.second.second << " " << group <<endl;
            int p = uf.getRoot(e.second.first);
            int q = uf.getRoot(e.second.second);
            // cerr << p << " " << q << endl;
            if(p == q) continue;
            const auto& ps = e.first.second;
            int x1 = (ps[0].x + ps[1].x)/2;
            int y1 = (ps[0].y + ps[1].y)/2;
            int x2 = (ps[2].x + ps[3].x)/2;
            int y2 = (ps[2].y + ps[3].y)/2;
            if(!path[x1][y1] || !path[x2][y2]) continue;
            bool hasWarp = false;
            for(int k=0;k<4;k++) if(warp[ps[k].x][ps[k].y].x != -1) hasWarp = true;
            if(hasWarp) continue;
            uf.merge(p, q);
            path[x1][y1] = 0;
            path[x2][y2] = 0;
            if(ps[0].x == ps[2].x || ps[0].y == ps[2].y){
                path[(ps[0].x+ps[2].x)/2][(ps[0].y+ps[2].y)/2] = 1;
            } else {
                warp[ps[0].x][ps[0].y] = ps[2];
                warp[ps[2].x][ps[2].y] = ps[0];
            }
            if(ps[1].x == ps[3].x || ps[1].y == ps[3].y){
                path[(ps[1].x+ps[3].x)/2][(ps[1].y+ps[3].y)/2] = 1;
            } else {
                warp[ps[1].x][ps[1].y] = ps[3];
                warp[ps[3].x][ps[3].y] = ps[1];
            }

            addCost += e.first.first;
            --group;
        }
        // if(group == 1 || group == curGroup){ curGroup = group; break; }
        curGroup = group;
    }
    cout << curGroup << " " << mcfResult.second + addCost << endl;
    if(currentCost < mcfResult.second + addCost) return current;

    if(curGroup == 1){
        vector<vector<int>> order(257, vector<int>(257, -1));
        {
            int x = 2*current[0].x + 128;
            int y = 2*current[0].y + 128;
            order[x][y] = 0;
            while(true){
                bool find = false;
                for(int d=0;d<4;d++){
                    int nx = x + dx[d];
                    if(nx < 0 || 256 < nx) continue;
                    int ny = y + dy[d];
                    if(ny < 0 || 256 < ny) continue;
                    if(!path[nx][ny] || order[nx][ny] != -1) continue;
                    order[nx][ny] = order[x][y];
                    x += 2 * dx[d];
                    y += 2 * dy[d];
                    order[x][y] = order[nx][ny] + 1;
                    find = true;
                    break;
                }
                if(!find){
                    if(warp[x][y].x == -1) break;
                    const auto& np = warp[x][y];
                    if(order[np.x][np.y] != -1) break;
                    order[np.x][np.y] = order[x][y] + 1;
                    x = np.x;
                    y = np.y;
                }
            }
            if(order[x][y] + 1 != current.size() || x/2 - 64 != current.back().x || y/2 - 64 != current.back().y){
                cerr << "The path is not valid" << endl;
                cerr << order[x][y] +1 << " " << current.size() << endl;
                cerr << (x/2-64) << " " << current.back().x << endl;
                cerr << (y/2-64) << " " << current.back().y << endl;
                return current;
            }
        }
        vector<P2> res(current.size());
        for(int x=0;x<=256;x+=2){
            for(int y=0;y<=256;y+=2){
                if(order[x][y] == -1) continue;
                res[order[x][y]].x = x/2 - 64;
                res[order[x][y]].y = y/2 - 64;
            }
        }
        return res;
    }
    return current;
}

vector<P2> optimizeBy4opt(const vector<P2>& current, const Image& image, const P2& offset){
    vector<vector<double>> cost(257, vector<double>(257, 0));

    auto colorCost = [&](int x1, int y1, int x2, int y2){
        const auto& p1 = image[offset.x + x1][offset.y + y1];
        const auto& p2 = image[offset.x + x2][offset.y + y2];
        double res = 0.0;
        res += abs(p1.r - p2.r);
        res += abs(p1.g - p2.g);
        res += abs(p1.b - p2.b);
        return res;
    };

    for(int x=-64;x<=64;x++){
        for(int y=-64;y<=64;y++){
            if(x+1 <= 64) cost[2*x+129][2*y+128] = colorCost(x, y, x+1, y);
            if(y+1 <= 64) cost[2*x+128][2*y+129] = colorCost(x, y, x, y+1);
        }
    }

    double currentCost = 0.0;
    vector<vector<int>> path(258, vector<int>(258, 0));
    for(auto& p : current) path[2*p.x+128][2*p.y+128] = 1;

    for(size_t i=0;i+1<current.size();i++){
        const int px = 2*current[i].x + 128;
        const int py = 2*current[i].y + 128;
        const int nx = 2*current[i+1].x + 128;
        const int ny = 2*current[i+1].y + 128;
        const int mx = (px+nx)/2;
        const int my = (py+ny)/2;
        path[mx][my] = 1;
        currentCost += cost[mx][my];
    }
    cerr << "CurrentCost: " << currentCost << endl;

    const double initial_temp = 0.5;
    const double final_temp = 0.01;

    XorShift rnd(randomValue());
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, -1, 0, 1};
    const int loopCnt = 100;
    Timer timer;
    double finalScore = currentCost;
    auto finalPath = path;

    for(int i=0;i<=loopCnt;i++){
        // if(i%1000 == 999) cerr << i+1 << " " << finalScore << " " << currentCost << endl;
        const double ratio = min(1.0, 2*i/(double)loopCnt);
        const double rev_ratio = 1 - ratio;
        const double temperature = initial_temp + (final_temp - initial_temp) * (1 - rev_ratio * rev_ratio * rev_ratio);

        if(i==0) timer.start();
        vector<vector<int>> order(257, vector<int>(257, -1));
        // for simulated annealing
        // if(i==loopCnt){
        //     path = finalPath;
        // }
        // record the visit order
        {
            int x = 2*current[0].x + 128;
            int y = 2*current[0].y + 128;
            order[x][y] = 0;
            while(true){
                bool find = false;
                for(int d=0;d<4;d++){
                    int nx = x + dx[d];
                    if(nx < 0 || 256 < nx) continue;
                    int ny = y + dy[d];
                    if(ny < 0 || 256 < ny) continue;
                    if(!path[nx][ny] || order[nx][ny] != -1) continue;
                    order[nx][ny] = order[x][y];
                    x += 2 * dx[d];
                    y += 2 * dy[d];
                    order[x][y] = order[nx][ny] + 1;
                    find = true;
                    break;
                }
                if(!find) break;
            }
            if(order[x][y] + 1 != current.size() || x/2 - 64 != current.back().x || y/2 - 64 != current.back().y){
                cerr << i << " " << "The path is not valid" << endl;
                cerr << order[x][y] +1 << " " << current.size() << endl;
                cerr << (x/2-64) << " " << current.back().x << endl;
                cerr << (y/2-64) << " " << current.back().y << endl;
                return current;
            }
        }
        if(i==0){ cerr << "Record visit order: " << timer.msec() << endl; timer.start(); }
        if(i == loopCnt){
            vector<P2> res(current.size());
            for(int x=0;x<=256;x+=2){
                for(int y=0;y<=256;y+=2){
                    if(order[x][y] == -1) continue;
                    res[order[x][y]].x = x/2 - 64;
                    res[order[x][y]].y = y/2 - 64;
                }
            }
            cerr << "Final cost: " << finalScore << endl;
            return res;
        }
        vector<P2> switchPoint;
        vector<double> switchCost;
        for(int x=1;x<=255;x+=2){
            for(int y=1;y<=255;y+=2){
                if(path[x-1][y] && path[x+1][y] && !path[x][y-1] && !path[x][y+1]){
                    switchPoint.emplace_back(x, y);
                    switchCost.push_back(cost[x][y-1] + cost[x][y+1] - cost[x-1][y] - cost[x+1][y]);
                } else if(path[x][y-1] && path[x][y+1] && !path[x-1][y] && !path[x+1][y]){
                    switchPoint.emplace_back(x, y);
                    switchCost.push_back(cost[x-1][y] + cost[x+1][y] - cost[x][y-1] - cost[x][y+1]);
                }
            }
        }
        if(switchPoint.size() <= 1) break;
        if(i==0){ cerr << "Find switch point: " << timer.msec() << endl; timer.start(); }

        // simulated annealing
/*
        for(int _=0;_<100;_++){
            int idx1 = rnd()%switchPoint.size();
            int idx2 = rnd()%switchPoint.size();
            if(idx1 == idx2) continue;
            if(switchPoint[idx1].x == switchPoint[idx2].x && abs(switchPoint[idx1].y - switchPoint[idx2].y) == 2) continue;
            if(switchPoint[idx1].y == switchPoint[idx2].y && abs(switchPoint[idx1].x - switchPoint[idx2].x) == 2) continue;
            const auto& p1 = switchPoint[idx1];
            const auto& p2 = switchPoint[idx2];
            int a, b, c, d;
            if(path[p1.x-1][p1.y]){
                a = order[p1.x-1][p1.y];
                b = order[p1.x+1][p1.y];
            } else {
                a = order[p1.x][p1.y-1];
                b = order[p1.x][p1.y+1];
            }
            if(path[p2.x-1][p2.y]){
                c = order[p2.x-1][p2.y];
                d = order[p2.x+1][p2.y];
            } else {
                c = order[p2.x][p2.y-1];
                d = order[p2.x][p2.y+1];
            }
            if(a > b) swap(a, b);
            if(!((a < c && c < b)^(a < d && d < b))) continue;
            double delta = switchCost[idx1] + switchCost[idx2];
            if(delta < 0 || bernoulli_distribution(exp(-delta/temperature))(rnd)){
                currentCost += delta;
                for(int k=0;k<4;k++){
                    path[p1.x+dx[k]][p1.y+dy[k]] = !path[p1.x+dx[k]][p1.y+dy[k]];
                    path[p2.x+dx[k]][p2.y+dy[k]] = !path[p2.x+dx[k]][p2.y+dy[k]];
                }
                switchCost[idx1] = -switchCost[idx1];
                switchCost[idx2] = -switchCost[idx2];
                if(currentCost < finalScore){
                    finalScore = currentCost;
                    finalPath = path;
                }
                break;
            }
        }
*/
        // greedy
        vector<pair<double, pair<int, int>>> candidate;
        for(int i=0;i<switchPoint.size();i++){
            for(int j=i+1;j<switchPoint.size();j++){
                if(switchPoint[i].x == switchPoint[j].x && abs(switchPoint[i].y - switchPoint[j].y) == 2) continue;
                if(switchPoint[i].y == switchPoint[j].y && abs(switchPoint[i].x - switchPoint[j].x) == 2) continue;
                double c = switchCost[i] + switchCost[j];
                if(c >= 0) continue;
                candidate.emplace_back(c, make_pair(i, j));
            }
        }
        if(candidate.empty()) break;
        sort(candidate.begin(), candidate.end());
        if(i==0){ cerr << "Sort candidates: " << timer.msec() << endl; timer.start(); }

        bool update = false;
        for(auto& cand : candidate){
            const int idx1 = cand.second.first;
            const int idx2 = cand.second.second;
            const auto& p1 = switchPoint[idx1];
            const auto& p2 = switchPoint[idx2];
            int a, b, c, d;
            if(path[p1.x-1][p1.y]){
                a = order[p1.x-1][p1.y];
                b = order[p1.x+1][p1.y];
            } else {
                a = order[p1.x][p1.y-1];
                b = order[p1.x][p1.y+1];
            }
            if(path[p2.x-1][p2.y]){
                c = order[p2.x-1][p2.y];
                d = order[p2.x+1][p2.y];
            } else {
                c = order[p2.x][p2.y-1];
                d = order[p2.x][p2.y+1];
            }
            if(a > b) swap(a, b);
            if(!((a < c && c < b)^(a < d && d < b))) continue;
            for(int k=0;k<4;k++){
                path[p1.x+dx[k]][p1.y+dy[k]] = !path[p1.x+dx[k]][p1.y+dy[k]];
                path[p2.x+dx[k]][p2.y+dy[k]] = !path[p2.x+dx[k]][p2.y+dy[k]];
            }
            switchCost[idx1] = -switchCost[idx1];
            switchCost[idx2] = -switchCost[idx2];
            currentCost += cand.first;
            cerr << "Cost " << i << ": " << currentCost << endl;
            update = true;
            break;
        }
        if(i==0){ cerr << "Checked candidates: " << timer.msec() << endl; timer.start(); }
        if(!update) i = loopCnt - 1;
    }
    cerr << "something wrong" << endl;
    return current;
}

Arms generateArmsFromPoint(const pair<P2, P2>& point){
    Arms res(8);
    res[0] = point.first;
    static int sz[] = {64, 32, 16, 8, 4, 2, 1, 1};
    const int sgnX = point.second.x > 0 ? 1 : -1;
    const int sgnY = point.second.y > 0 ? 1 : -1;
    int x = abs(point.second.x);
    int y = abs(point.second.y);
    for(int i=7;i>=1;i--){
        const int px = min(x, sz[i]);
        const int py = min(y, sz[i]);
        res[i].x = sgnX * px;
        res[i].y = sgnY * py;
        x -= px;
        y -= py;
    }
    return res;
}

Solution generateSolution(const vector<pair<P2, P2>>& route){
    Solution res;
    auto current = generateArmsFromPoint(route.front());
    res.push_back(current);
    static int sz[] = {64, 32, 16, 8, 4, 2, 1, 1};
    for(int i=1;i<route.size();i++){
        auto tmp = current;
        current[0] = route[i].first;
        int dx = route[i].second.x - route[i-1].second.x;
        int dy = route[i].second.y - route[i-1].second.y;
        // TODO: It can generate invalid moves. Currently fixed by hand,
        //       but would like to replace with a better method.
        while(dx != 0 || dy != 0){
            for(int j=3;j<8;j++){
                if(dx < 0 && current[j].x > 0){
                    --current[j].x;
                    ++dx;
                }
                if(dx > 0 && current[j].x < 0){
                    ++current[j].x;
                    --dx;
                }
                if(dy < 0 && current[j].y > 0){
                    --current[j].y;
                    ++dy;
                }
                if(dy > 0 && current[j].y < 0){
                    ++current[j].y;
                    --dy;
                }
            }
            if(dx * route[i].second.x > 0){
                for(int j=1;j<8;j++){
                    if(dx < 0){
                        if(current[j].x != -sz[j]){
                            --current[j].x;
                            ++dx;
                        }
                    }
                    if(dx > 0){
                        if(current[j].x != sz[j]){
                            ++current[j].x;
                            --dx;
                        }
                    }
                }
            } else {
                for(int j=7;j>=1;j--){
                    if(dx < 0){
                        if(current[j].x != -sz[j]){
                            --current[j].x;
                            ++dx;
                        }
                    }
                    if(dx > 0){
                        if(current[j].x != sz[j]){
                            ++current[j].x;
                            --dx;
                        }
                    }
                }
            }
            if(dy * route[i].second.y > 0){
                for(int j=1;j<8;j++){
                    if(dy < 0){
                        if(current[j].y != -sz[j]){
                            --current[j].y;
                            ++dy;
                        }
                    }
                    if(dy > 0){
                        if(current[j].y != sz[j]){
                            ++current[j].y;
                            --dy;
                        }
                    }
                }
            } else {
                for(int j=7;j>=1;j--){
                    if(dy < 0){
                        if(current[j].y != -sz[j]){
                            --current[j].y;
                            ++dy;
                        }
                    }
                    if(dy > 0){
                        if(current[j].y != sz[j]){
                            ++current[j].y;
                            --dy;
                        }
                    }
                }
            }
        }
        if(dx != 0 || dy != 0){
            for(auto& p : tmp) cerr << "(" << p.x << "," << p.y << ")";
            cerr << endl;
            for(auto& p : current) cerr << "(" << p.x << "," << p.y << ")";
            cerr << endl;
            cerr << "dx = " << route[i].second.x - route[i-1].second.x << endl;
            cerr << "dy = " << route[i].second.y - route[i-1].second.y << endl;
            cerr << "ERROR!" << endl;
        }
        res.push_back(current);
    }
    res.back() = res.front();
    for(int i=res.size()-1;i>=0;i--){
        vector<int> plus, minus;
        for(int j=1;j<8;j++){
            if(res[i-1][j].y - res[i][j].y > 0) plus.push_back(j);
            if(res[i-1][j].y - res[i][j].y < 0) minus.push_back(j);
        }
        if(plus.empty() && minus.empty()) break;
        const int m = min(plus.size(), minus.size());
        for(int j=0;j<m;j++){
            res[i-1][plus[j]].y = res[i][plus[j]].y + 1;
            res[i-1][minus[j]].y = res[i][minus[j]].y - 1;
        }
        for(int j=m;j<plus.size();j++) res[i-1][plus[j]].y = res[i][plus[j]].y;
        for(int j=m;j<minus.size();j++) res[i-1][minus[j]].y = res[i][minus[j]].y;
    }
    return res;
}

Solution generateSolutionByBeamImpl(const vector<pair<P2, P2>>& _route){
    cerr << "start beam " << endl;
    cerr << _route.front().first.x << " " << _route.front().first.y << " " << _route.front().second.x << " " << _route.front().second.y << endl;
    cerr << _route.back().first.x << " " << _route.back().first.y << " " << _route.back().second.x << " " << _route.back().second.y << endl;
    vector<P2> moves;
    for(int i=0;i+1<_route.size();i++){
        const auto& next = _route[i+1];
        const auto& cur = _route[i];
        moves.emplace_back(
            next.first.x + next.second.x - cur.first.x - cur.second.x,
            next.first.y + next.second.y - cur.first.y - cur.second.y
        );
    }
    auto start = generateArmsFromPoint(_route.front());
    static int sz[] = {64, 32, 16, 8, 4, 2, 1, 1};
    auto idx64 = [](const P2& p){
        return min(511, 2 * (p.x + p.y + 128) - (p.x > p.y ? 1 : 0));
    };
    auto idx32 = [](const P2& p){
        return 0;
        // return min(255, 2 * (p.x + p.y + 64) - (p.x > p.y ? 1 : 0));
    };
    auto armsComp = [](const Arms& a, const Arms& b){
        auto armsScore = [](const Arms& a){
            int sa = 1, sb = 1, sc = 1, sd = 1;
            for(int i=0;i<8;i++){
                if(abs(a[i].x) == sz[i]){
                    if(a[i].y != -sz[i]) ++sc;
                    if(a[i].y != sz[i]) ++sd;
                }
                if(abs(a[i].y) == sz[i]){
                    if(a[i].x != -sz[i]) ++sa;
                    if(a[i].x != sz[i]) ++sb;
                }
            }
            return sa * sb * sc * sd;
        };
        return armsScore(a) < armsScore(b);
    };
    using BeamQueue = priority_queue<Arms, vector<Arms>, decltype(armsComp)>;
    vector<vector<vector<BeamQueue>>> qu(2, vector<vector<BeamQueue>>(512, vector<BeamQueue>(256, BeamQueue(armsComp))));
    qu[0][idx64(start[0])][idx32(start[1])].push(start);
    map<Arms, Arms> previous;
    int quIdx = 0;
    vector<vector<vector<int>>> mask(256, vector<vector<int>>(9));
    for(int i=0;i<256;i++){
        int c = 0;
        for(int j=0;j<8;j++) if(i&(1<<j)) ++c;
        for(int j=0;j<256;j++){
            if((i&j) == i) mask[j][c].push_back(i);
        }
    }
    int seek = 0;
    for(const auto& move : moves){
        auto& curQu = qu[quIdx];
        auto& nextQu = qu[1-quIdx];
        int rest = 100;
        auto moveNext = [&](const Arms& arms){
            int maskX = 0, cntX = 0;
            int maskY = 0, cntY = 0;
            if(move.x != 0){
                cntX = abs(move.x);
                for(int i=0;i<8;i++){
                    if(abs(arms[i].y) != sz[i]) continue;
                    if(move.x > 0 && arms[i].x == sz[i]) continue;
                    if(move.x < 0 && arms[i].x == -sz[i]) continue;
                    maskX |= (1 << i);
                }
            }
            if(move.y != 0){
                cntY = abs(move.y);
                for(int i=0;i<8;i++){
                    if(abs(arms[i].x) != sz[i]) continue;
                    if(move.y > 0 && arms[i].y == sz[i]) continue;
                    if(move.y < 0 && arms[i].y == -sz[i]) continue;
                    maskY |= (1 << i);
                }
            }
            for(int mx : mask[maskX][cntX]){
                for(int my : mask[maskY][cntY]){
                    auto nextArm = arms;
                    for(int i=0;i<8;i++){
                        if(mx&(1<<i)){
                            if(move.x > 0) ++nextArm[i].x;
                            else --nextArm[i].x;
                        }
                        if(my&(1<<i)){
                            if(move.y > 0) ++nextArm[i].y;
                            else --nextArm[i].y;
                        }
                    }
                    if(previous.count(nextArm)) continue;
                    previous[nextArm] = arms;
                    nextQu[idx64(nextArm[0])][idx32(nextArm[1])].push(nextArm);
                }
            }
            --rest;
        };
        for(int _=0;_<1;_++){
            for(auto& vv : curQu){
                for(auto& q : vv){
                    if(q.empty()) continue;
                    moveNext(q.top());
                    q.pop();
                }
            }
        }
        if(rest > 0){
            BeamQueue restQu(armsComp);
            for(auto& vv : curQu){
                for(auto& q : vv){
                    while(!q.empty()){
                        restQu.push(q.top());
                        q.pop();
                    }
                }
            }
            while(!restQu.empty() && rest > 0){
                moveNext(restQu.top());
                restQu.pop();
            }
        } else {
            for(auto& vv : curQu){
                for(auto& q : vv){
                    while(!q.empty()) q.pop();
                }
            }
        }
        cerr << ++seek << "/" << moves.size() << " " << move.x << " " << move.y << " " << rest << "                   \r";
        if(rest == 200) break;
        quIdx = 1 - quIdx;
    }
    cerr << "\n";
    Solution res;
    auto end = generateArmsFromPoint(_route.back());
    if(previous.count(end)){
        res.push_back(end);
        auto cur = previous[end];
        while(cur != start){
            res.push_back(cur);
            cur = previous[cur];
        }
        res.push_back(start);
        reverse(res.begin(), res.end());
    } else {
        cerr << "Could not find valid move" << endl;
    }
    return res;
}

Solution generateSolutionByBeam(const vector<pair<P2, P2>>& _route){
    Solution res;
    int idx = 0;
    while(idx+1 < _route.size()){
        vector<pair<P2, P2>> route;
        route.push_back(_route[idx++]);
        while(true){
            const auto& p = _route[idx];
            route.push_back(p);
            const int x = p.first.x + p.second.x;
            const int y = p.first.y + p.second.y;
            if((x == 0 && y == 0) || (abs(x) == 128 && abs(y) == 128)){
                break;
            }
            ++idx;
        }
        if(idx+1 == _route.size()){
            reverse(route.begin(), route.end());
        }
        auto part = generateSolutionByBeamImpl(route);
        if(part.empty()) return Solution();
        if(idx+1 == _route.size()){
            reverse(part.begin(), part.end());
        }
        for(int i=0;i+1<part.size();i++) res.push_back(part[i]);
        if(idx+1 == _route.size()) res.push_back(part.back());
    }
    return res;
}

vector<pair<P2, P2>> generateRoute(const Solution& solution){
    vector<pair<P2, P2>> res;
    for(auto& s : solution){
        P2 p(0, 0);
        for(int i=1;i<s.size();i++){
            p.x += s[i].x;
            p.y += s[i].y;
        }
        res.emplace_back(s[0], p);
    }
    return res;
}

template<typename T>
Solution improveSolution(const Solution& solution, const Image& image, const T& optimizeFunction){
    auto route = generateRoute(solution);
    const int y1[] = {64, 64, -64, -64};
    const int x2[] = {-64, 64, 64, -64};
    int quad = 0;
    int idx = 0;
    vector<pair<P2, P2>> newRoute;
    while(idx < route.size()){
        if(quad == 4 || route[idx].first.y != y1[quad] || route[idx].second.x != x2[quad]){
            newRoute.push_back(route[idx]);
            ++idx;
            continue;
        }
        vector<P2> points;
        while(idx < route.size() && route[idx].first.y == y1[quad] && route[idx].second.x == x2[quad]){
            points.emplace_back(route[idx].first.x, route[idx].second.y);
            ++idx;
        }
        if(quad == 3){
            points.pop_back();
            --idx;
        }
        P2 offset(x2[quad] + 128, y1[quad] + 128);
        points = optimizeFunction(points, image, offset);
        for(const auto& p : points){
            newRoute.emplace_back(P2(p.x, y1[quad]), P2(x2[quad], p.y));
        }
        ++quad;
    }
    return generateSolution(newRoute);
}

Solution simpleRoute(){
    return generateSolution(simpleRouteP2());
}

void checkTop(const Image& image){
    auto colorCost = [&](int x1, int y1, int x2, int y2){
        const auto& p1 = image[x1][y1];
        const auto& p2 = image[x2][y2];
        double res = 0.0;
        res += abs(p1.r - p2.r);
        res += abs(p1.g - p2.g);
        res += abs(p1.b - p2.b);
        return res;
    };
    vector<double> cost(256);
    for(int i=0;i<256;i++) cost[i] = colorCost(i, 256, i+1, 256);
    for(int i=0;i<=128;i+=2){
        double sum = 0.0;
        for(int j=0;j<128;j++) sum += cost[i+j];
        cout << i << " " << sum << endl;
    }
    for(int i=0;i<256;i++) cost[i] = colorCost(256, 256-i, 256, 256-i-1);
    for(int i=0;i<=128;i+=2){
        double sum = 0.0;
        for(int j=0;j<128;j++) sum += cost[i+j];
        cout << i << " " << sum << endl;
    }
    for(int i=0;i<256;i++) cost[i] = colorCost(256-i, 0, 256-i-1, 0);
    for(int i=0;i<=128;i+=2){
        double sum = 0.0;
        for(int j=0;j<128;j++) sum += cost[i+j];
        cout << i << " " << sum << endl;
    }
}

int main(){
    // Code to fix the invalid output by hand
    {
        const auto image = loadImage("image.csv");
        // solution = improveSolution(solution, image, optimizeByMCF);
        auto solution = loadSolution("output.csv");
        solution = generateSolutionByBeam(generateRoute(solution));
        cout << solution.size() << endl;
        cout << validateSolution(solution) << endl;
        printf("%.9lf\n", calcScore(solution, image));
        printSolution(solution, "output.csv");
        return 0;
    }
    const auto image = loadImage("image.csv");
    // To generate baseline solution (score=75274)
    // auto solution = improveSolution(simpleRoute(), image, optimizeByMCF);
    // Improve solution by using LKH
    auto solution = improveSolution(loadSolution("best75274.csv"), image, optimizeByLKH);
    cout << solution.size() << endl;
    cout << validateSolution(solution) << endl;
    printf("%.9lf\n", calcScore(solution, image));
    printSolution(solution, "output.csv");
}
