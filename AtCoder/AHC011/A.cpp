#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
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
} timer;

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
template<typename CAP, typename COST>
class MinCostFlow {
public:
    explicit MinCostFlow(int N) : g(N) {}
    void addEdge(int src, int dst, CAP cap, COST cost){
        int r1 = g[src].size();
        int r2 = g[dst].size();
        g[src].emplace_back(src, dst, cap, cost, r2);
        g[dst].emplace_back(dst, src, 0, -cost, r1);
    }
    pair<COST, CAP> solve(int s, int t, CAP maxFlow){
        const int n = g.size();
        pair<COST, CAP> res = make_pair(0, 0);
        vector<COST> h(n, 0);
        while(maxFlow > 0){
            vector<COST> dist(n, INF); dist[s] = 0;
            vector<pair<int, int>> prev(n, make_pair(-1, -1));
            priority_queue<pair<COST, int>, vector<pair<COST, int>>, greater<pair<COST, int>>> qu;
            qu.emplace(0, s);
            while(!qu.empty()){
                auto e = qu.top(); qu.pop();
                if(dist[e.second] < e.first) continue;
                for(int i=0;i<g[e.second].size();i++){
                    auto& p = g[e.second][i];
                    if(p.cap > 0 && dist[p.dst] > dist[p.src] + p.cost + h[p.src] - h[p.dst]){
                        dist[p.dst] = dist[p.src] + p.cost + h[p.src] - h[p.dst];
                        prev[p.dst] = make_pair(p.src, i);
                        qu.emplace(dist[p.dst], p.dst);
                    }
                }
            }
            if(prev[t].first == -1) break;
            CAP f = maxFlow;
            for(int u=t;u!=s;u=prev[u].first) f = min(f, g[prev[u].first][prev[u].second].cap);
            for(int u=t;u!=s;u=prev[u].first){
                auto& p = g[prev[u].first][prev[u].second];
                auto& q = g[p.dst][p.rev];
                res.first += f * p.cost;
                p.cap -= f;
                q.cap += f;
            }
            res.second += f;
            for(int i=0;i<n;i++) h[i] += dist[i];
            maxFlow -= f;
        }
        return res;
    }
    vector<int> getPerm(int N2){
        vector<int> res(N2, 0);
        for(int i=0;i<N2;i++){
            for(auto& e : g[i+1]){
                if(!e.cap) res[i] = e.dst - N2 - 1;
            }
        }
        return res;
    }
private:
    class Edge {
    public:
        explicit Edge(int src, int dst, CAP cap, COST cost, int rev) : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
        const int src;
        const int dst;
        CAP cap;
        COST cost;
        const int rev;
    };
private:
    const COST INF = 1LL << 30;
    vector<vector<Edge>> g;
};

//------------------------------------------------------------------------------
void showBoard(const vector<int>& board, int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << char(board[i*N+j] < 10 ? board[i*N+j]+'0' : board[i*N+j]-10+'a');
        }
        cout << endl;
    }
}

//------------------------------------------------------------------------------
std::string naiveSearch(const vector<int>& start, const vector<int>& target, int N){
    unordered_map<unsigned long long, unsigned long long> mp;
    int sx, sy;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(!start[i*N+j]){
                sx = i;
                sy = j;
                break;
            }
        }
    }
    long long initial = 4*sx+sy;
    for(auto t : start) initial = 16 * initial + t;
    mp[initial] = 0xFFFFFFFFFFFFFFFFULL;
    long long goal = 0;
    for(auto t : target) goal = 16 * goal + t;
    queue<unsigned long long> qu; qu.push(initial);
    auto mask = [](int b){ return (1ULL << b) - 1; };
    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {-1, 0, 1, 0};
    auto printBitBoard = [&N](unsigned long long b){
        vector<int> cur;
        for(int j=4*N*N-4;j>=0;j-=4) cur.push_back((b>>j)%16);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) cout << cur[i*N+j] << " ";
            cout << endl;
        }
    };

    while(!qu.empty()){
        auto p = qu.front(); qu.pop();
        if((p&mask(4*N*N)) == goal){
            string res = "";
            while(p != initial){
                vector<int> cur;
                for(int j=4*N*N-4;j>=0;j-=4) cur.push_back((p>>j)%16);
                auto pre = mp[p];
                res.push_back("LURD"[pre>>(4*N*N+4)]);
                p = (pre&mask(4*N*N+4));
            }
            reverse(res.begin(), res.end());
            return res;
        }
        const int x = (p >> (4*N*N+2));
        const int y = (p >> (4*N*N))%4;

        for(int i=0;i<4;i++){
            const int nx = x + dx[i];
            const int ny = y + dy[i];
            if(nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
            int cur = N * N - 1 - (x * N + y);
            int dst = N * N - 1 - (nx * N + ny);
            auto next = (p&mask(4*N*N));
            int value = (next >> (4*dst))%16;
            next &= ~(15ULL << (4*dst));
            next |= (value << (4*cur));
            next |= ((4*nx+ny) << (4*N*N));
            if(mp.count(next)) continue;
            mp[next] = (p | (((unsigned long long)i) << (4*N*N+4)));
            qu.push(next);
        }
    }
    assert(false);
    return "";
}

//------------------------------------------------------------------------------
template<int N>
std::string solveSlide(const vector<int>& start, const vector<int>& target){
    int doubleNum = 0;
    vector<int> restNum(16, 0);
    auto board = start;
    int blankPos = -1;
    for(auto& t : board) ++restNum[t];
    for(auto& t : restNum) if(t >= 2) ++doubleNum;
    for(int i=0;i<start.size();i++) if(!start[i]) blankPos = i;
    vector<int> lock(N*N, 0);
    static int step[N*N][N*N];
    static int step2[N*N][N*N][N*N];
    static int prev2[N*N][N*N][N*N];
    int lineX = 0, lineY = 0;
    auto getDist = [&](int src, int dst){
        return abs(src%N - dst%N) + abs(src/N - dst/N);
    };
    auto toValue = [&](int x, int y){ return x*N+y; };
    auto search2 = [&](int dst1, int panel1, int dst2, int panel2){
        const int d[] = {1, N, -1, -N};
        const int dx[] = {0, -1, 0, 1};
        const int dy[] = {-1, 0, 1, 0};
        memset(step2, -1, sizeof(step2));
        queue<int> qu;
        auto pack = [&](int a, int b, int c){ return (a << 16)|(b << 8)|c; };
        auto findStart = [&](int sx, int sy){
            for(int i=0;i<4;i++){
                const int nx = sx + dx[i];
                const int ny = sy + dy[i];
                if(nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
                const int p = toValue(nx, ny);
                if(lock[p]) continue;
                if(p == dst1) continue;
                if(panel2 != -1 && p == dst2) continue;
                const int c = pack(dst1, dst2, p);
                qu.push(c);
                step2[dst1][dst2][p] = 0;
                prev2[dst1][dst2][p] = -1;
            }
        };
        findStart(dst1/N, dst1%N);
        if(panel2 != -1) findStart(dst2/N, dst2%N);
        const bool checkParity = [&](){
            if(doubleNum == 1){
                if(restNum[panel1] == 2) return true;
                if(panel2 != -1 && restNum[panel2] == 2) return true;
                if(panel1 == panel2 && restNum[panel1] == 3) return true;
            } else if(doubleNum == 2){
                if(panel2 != -1 && panel1 != panel2){
                    return (restNum[panel1] == 2 && restNum[panel2] == 2);
                }
            }
            return false;
        }();
        vector<int> freePos;
        if(checkParity){
            for(int k=0;k<N*N;k++){
                if(!lock[k]) freePos.push_back(k);
            }
        }
        while(!qu.empty()){
            const int tmp = qu.front(); qu.pop();
            const int pos1 = (tmp >> 16);
            const int pos2 = (tmp >> 8)%256;
            const int posBlank = tmp%256;
            if(board[pos1] == panel1 && board[posBlank] == 0){
                if(panel2 == -1 || board[pos2] == panel2){
                    bool ok = true;
                    if(checkParity){
                        vector<int> checked(freePos.size(), 0);
                        vector<int> perm(freePos.size(), -1);
                        for(int a=0;a<freePos.size();a++){
                            for(int b=0;b<freePos.size();b++){
                                if(freePos[a] == pos1 && freePos[b] == dst1){
                                    perm[a] = b;
                                    checked[b] = 1;
                                }
                                if(panel2 != -1 && freePos[a] == pos2 && freePos[b] == dst2){
                                    perm[a] = b;
                                    checked[b] = 1;
                                }
                            }
                        }
                        int distBlank = 0;
                        for(int a=0;a<freePos.size();a++){
                            if(perm[a] != -1) continue;
                            for(int b=0;b<freePos.size();b++){
                                if(checked[b]) continue;
                                if(board[freePos[a]] == target[freePos[b]]){
                                    perm[a] = b;
                                    checked[b] = 1;
                                    if(!target[freePos[b]]) distBlank = getDist(freePos[a], freePos[b]);
                                    break;
                                }
                            }
                        }
                        for(int a=0;a<freePos.size();a++){
                            if(perm[a] == a) continue;
                            for(int b=a+1;b<freePos.size();b++){
                                if(perm[b] == a){
                                    swap(perm[a], perm[b]);
                                    ++distBlank;
                                }
                            }
                        }
                        if(distBlank%2) ok = false;
                    }
                    if(ok){
                        string res;
                        int p1 = pos1;
                        int p2 = pos2;
                        int pb = posBlank;
                        res.reserve(step2[p1][p2][pb]);
                        while(prev2[p1][p2][pb] != -1){
                            const int mv = prev2[p1][p2][pb];
                            const int nb = pb + d[mv];
                            res.push_back("RDLU"[mv]);
                            swap(board[pb], board[nb]);
                            if(p1 == nb){
                                p1 = pb;
                            } else if(panel2 != -1 && p2 == nb){
                                p2 = pb;
                            }
                            pb = nb;
                        }
                        lock[dst1] = 1;
                        --restNum[panel1];
                        if(restNum[panel1] == 1) --doubleNum;
                        if(panel2 != -1){
                            lock[dst2] = 1;
                            --restNum[panel2];
                            if(restNum[panel2] == 1) --doubleNum;
                        }
                        return res;
                    }
                }
            }
            const int bx = posBlank/N;
            const int by = posBlank%N;
            for(int i=0;i<4;i++){
                const int nx = bx + dx[i];
                const int ny = by + dy[i];
                if(nx < 0 || N <= nx || ny < 0 || N <= ny) continue;
                const int p = toValue(nx, ny);
                if(lock[p]) continue;
                const int np1 = (pos1 == p ? posBlank : pos1);
                const int np2 = (panel2 != -1 && pos2 == p ? posBlank : pos2);
                if(step2[np1][np2][p] != -1) continue;
                step2[np1][np2][p] = step2[pos1][pos2][posBlank] + 1;
                prev2[np1][np2][p] = i;
                qu.push(pack(np1, np2, p));
            }
        }
        assert(false);
    };
    string res = "";
    while(lineX < N-2 || lineY < N-2){
        int from, to, dir;
        if(lineX == lineY){
            if(getDist(toValue(lineX, N-1), blankPos) <= getDist(toValue(N-1, lineY), blankPos)){
                from = toValue(lineX, N-1);
                to = toValue(lineX, lineY);
                dir = -1;
            } else {
                from = toValue(N-1, lineY);
                to = toValue(lineX, lineY);
                dir = -N;
            }
        } else if(lineX < lineY){
            if(getDist(toValue(lineX, lineY), blankPos) <= getDist(toValue(lineX, N-1), blankPos)){
                from = toValue(lineX, lineY);
                to = toValue(lineX, N-1);
                dir = 1;
            } else {
                from = toValue(lineX, N-1);
                to = toValue(lineX, lineY);
                dir = -1;
            }
        } else {
            if(getDist(toValue(lineX, lineY), blankPos) <= getDist(toValue(N-1, lineY), blankPos)){
                from = toValue(lineX, lineY);
                to = toValue(N-1, lineY);
                dir = N;
            } else {
                from = toValue(N-1, lineY);
                to = toValue(lineX, lineY);
                dir = -N;
            }
        }
        while(from != to){
            if(from+dir == to){
                res.append(search2(from, target[from], to, target[to]));
                from = to;
            } else if(from+2*dir == to){
                res.append(search2(from, target[from], 0, -1));
                from += dir;
            } else {
                res.append(search2(from, target[from], from+dir, target[from+dir]));
                from += 2*dir;
            }
        }
        if(abs(dir) == N){
            ++lineY;
        } else {
            ++lineX;
        }
    }
    vector<int> lastStart((N-lineX)*(N-lineX));
    vector<int> lastTarget((N-lineX)*(N-lineX));
    int idx = 0;
    for(int i=lineX;i<N;i++){
        for(int j=lineY;j<N;j++){
            lastStart[idx] = board[i*N+j];
            lastTarget[idx] = target[i*N+j];
            ++idx;
        }
    }
    res.append(naiveSearch(lastStart, lastTarget, N-lineX));
    return res;
}

//------------------------------------------------------------------------------
class Solver {
public:
    explicit Solver(const vector<string>& vs)
        : N(vs.size())
        , mBestSize(0)
        , mBestFill(0)
        , mLowNum(0)
        , mRoot(vs.size()*vs.size(), -1)
        , mSize(vs.size()*vs.size(), 1)
        , mOuter(vs.size()*vs.size(), 0)
        , mCurTarget(vs.size()*vs.size(), -1)
        , mTarget(vs.size()*vs.size(), -1)
        , mStart(vs.size()*vs.size(), 0)
        , mPanelNum(16, 0)
    {
        solve_(vs);
    }
private:
    void solve_(const vector<string>& vs){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                const int v = isdigit(vs[i][j]) ? vs[i][j] - '0' : vs[i][j] - 'a' + 10;
                mStart[i*N+j] = v;
                if(v) ++mPanelNum[v];
                if(v >= 8) ++mLowNum;
            }
        }
        search_(0);
        fill(mPanelNum.begin(), mPanelNum.end(), 0);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                const int v = isdigit(vs[i][j]) ? vs[i][j] - '0' : vs[i][j] - 'a' + 10;
                ++mPanelNum[v];
                if(mTarget[i*N+j] != -1) --mPanelNum[mTarget[i*N+j]];
            }
        }
        mCurTarget = mTarget;
        UnionFind uf(N*N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(mTarget[i*N+j] == -1) continue;
                if(j+1 < N && mTarget[i*N+j+1] != -1){
                    if((mTarget[i*N+j]&4) && (mTarget[i*N+j+1]&1)){
                        uf.merge(i*N+j, i*N+j+1);
                    }
                }
                if(i+1 < N && mTarget[i*N+j+N] != -1){
                    if((mTarget[i*N+j]&8) && (mTarget[i*N+j+N]&2)){
                        uf.merge(i*N+j, i*N+j+N);
                    }
                }
            }
        }
        for(int i=0;i<N*N;i++){
            if(mTarget[i] == -1){
                mRoot[i] = -1;
                mSize[i] = 1;
            } else {
                const int r = uf.getRoot(i);
                mRoot[i] = i == r ? -1 : r;
                mSize[i] = uf.getSize(r);
            }
        }
        search2_(mBestFill);

        cout << calcMove_() << endl;

    }
    int getRoot_(int v) const {
        return mRoot[v] == -1 ? v : getRoot_(mRoot[v]);
    }
    int getSize_(int v) const {
        return mSize[getRoot_(v)];
    }
    void search_(int pos){
        if(pos == N*N-1 || timer.msec() > 2000) return;
        if(max(1, N*N-N-pos) <= mLowNum) return;
        const int x = pos/N;
        const int y = pos%N;
        int start = 0;
        if(y && (mCurTarget[pos-1]&4)) start |= 1;
        if(x && (mCurTarget[pos-N]&8)) start |= 2;
        const int rootY = (start&1) ? getRoot_(pos-1) : -1;
        const int rootX = (start&2) ? getRoot_(pos-N) : -1;
        if(start && (rootY == rootX)) return;
        const int inc = (y == N-1 || pos == N*N-2) ? 8 : 4;
        const int end = (x == N-1 || pos == N*N-N-1) ? 8 : 16;

        vector<int> cand;
        cand.reserve(4);
        for(int i=start;i<end;i+=inc){
            if(mPanelNum[i]) cand.push_back(i);
        }
        sort(cand.begin(), cand.end(), [&](int a, int b){
            return mPanelNum[a] > mPanelNum[b];
        });

        for(int i : cand){
            if(!mPanelNum[i]) continue;
            mCurTarget[pos] = i;
            --mPanelNum[i];
            mLowNum -= i/8;
            bool ok = true;
            int curSize = 1;
            if(start == 0){
                mOuter[pos] = (i/4+1)/2;
            } else if(start == 1){
                mRoot[pos] = rootY;
                ++mSize[rootY];
                --mOuter[rootY];
                mOuter[rootY] += (i/4+1)/2;
                if(!mOuter[rootY]) ok = false;
                curSize = mSize[rootY];
            } else if(start == 2){
                mRoot[pos] = rootX;
                ++mSize[rootX];
                --mOuter[rootX];
                mOuter[rootX] += (i/4+1)/2;
                if(!mOuter[rootX]) ok = false;
                curSize = mSize[rootX];
            } else if(start == 3){
                mRoot[pos] = rootY;
                mRoot[rootX] = rootY;
                mSize[rootY] += mSize[rootX] + 1;
                mOuter[rootY] += (i/4+1)/2 + mOuter[rootX] - 2;
                if(!mOuter[rootY]) ok = false;
                curSize = mSize[rootY];
            }
            if(ok || pos == N*N-2){
                if(curSize > mBestSize || (curSize == mBestSize && pos+1 > mBestFill)){
                    mBestSize = curSize;
                    mBestFill = pos+1;
                    mTarget = mCurTarget;
                }
                search_(pos+1);
                if(mBestSize == N*N-1) break;
            }
            if(start == 0){
                mOuter[pos] = 0;
            } else if(start == 1){
                mRoot[pos] = -1;
                --mSize[rootY];
                ++mOuter[rootY];
                mOuter[rootY] -= (i/4+1)/2;
            } else if(start == 2){
                mRoot[pos] = -1;
                --mSize[rootX];
                ++mOuter[rootX];
                mOuter[rootX] -= (i/4+1)/2;
            } else if(start == 3){
                mRoot[pos] = -1;
                mRoot[rootX] = -1;
                mSize[rootY] -= mSize[rootX] + 1;
                mOuter[rootY] -= (i/4+1)/2 + mOuter[rootX] - 2;
            }
            mCurTarget[pos] = -1;
            ++mPanelNum[i];
            mLowNum += i/8;
        }
    }
    void search2_(int pos){
        if(pos == N*N || timer.msec() > 2100) return;
        const int x = pos/N;
        const int y = pos%N;
        int start = 0;
        if(y && (mCurTarget[pos-1]&4)) start |= 1;
        if(x && (mCurTarget[pos-N]&8)) start |= 2;
        const int rootY = (start&1) ? getRoot_(pos-1) : -1;
        const int rootX = (start&2) ? getRoot_(pos-N) : -1;
        for(int i=15;i>=0;i--){
            if(!mPanelNum[i]) continue;
            const int join = (start&i);
            if(join == 3 && rootX == rootY) continue;
            mCurTarget[pos] = i;
            --mPanelNum[i];
            bool ok = true;
            int curSize = mBestSize;
            if(join == 1){
                mRoot[pos] = rootY;
                ++mSize[rootY];
                curSize = mSize[rootY];
            } else if(join == 2){
                mRoot[pos] = rootX;
                ++mSize[rootX];
                curSize = mSize[rootX];
            } else if(join == 3){
                mRoot[pos] = rootY;
                mRoot[rootX] = rootY;
                mSize[rootY] += mSize[rootX] + 1;
                curSize = mSize[rootY];
            }
            if(curSize > mBestSize || (curSize == mBestSize && pos+1 > mBestFill)){
                mBestSize = curSize;
                mBestFill = pos+1;
                mTarget = mCurTarget;
            }
            search2_(pos+1);
            if(mBestSize == N*N-1 || mBestFill == N*N) break;
            if(join == 1){
                mRoot[pos] = -1;
                --mSize[rootY];
            } else if(join == 2){
                mRoot[pos] = -1;
                --mSize[rootX];
            } else if(join == 3){
                mRoot[pos] = -1;
                mRoot[rootX] = -1;
                mSize[rootY] -= mSize[rootX] + 1;
            }
            mCurTarget[pos] = -1;
            ++mPanelNum[i];
        }
    }
    std::string calcMove_() const {
        if(N == 6) return solveSlide<6>(mStart, mTarget);
        if(N == 7) return solveSlide<7>(mStart, mTarget);
        if(N == 8) return solveSlide<8>(mStart, mTarget);
        if(N == 9) return solveSlide<9>(mStart, mTarget);
        return solveSlide<10>(mStart, mTarget);
        // MinCostFlow<int, int> mcf(2*N*N+2);
        // auto getDist = [&](int src, int dst){
        //     return abs(src%N - dst%N) + abs(src/N - dst/N);
        // };
        // for(int i=0;i<N*N;i++){
        //     mcf.addEdge(0, i+1, 1, 0);
        //     mcf.addEdge(N*N+1+i, 2*N*N+1, 1, 0);
        //     for(int j=0;j<N*N;j++){
        //         if(mStart[i] != mTarget[j]) continue;
        //         int dist = abs(i%N - j%N) + abs(i/N - j/N);
        //         mcf.addEdge(i+1, j+N*N+1, 1, getDist(i, j));
        //     }
        // }
        // auto res = mcf.solve(0, 2*N*N+1, N*N);
    }
private:
    int N;
    int mBestSize;
    int mBestFill;
    int mLowNum;
    vector<int> mRoot;
    vector<int> mSize;
    vector<int> mOuter;
    vector<int> mTarget;
    vector<int> mCurTarget;
    vector<int> mStart;
    vector<int> mPanelNum;
};

//------------------------------------------------------------------------------
int main(){
    int N, T; cin >> N >> T;
    vector<string> vs(N);
    for(auto& t : vs) cin >> t;
    Solver solver(vs);
}