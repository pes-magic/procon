#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <functional>
#include <cstdlib>

using namespace std;

class Timer {
public:
	explicit Timer()
		: mStart(chrono::system_clock::now())
	{}
	void start() { mStart = chrono::system_clock::now(); }
	double sec() const {
		auto t = chrono::system_clock::now();
		return 1e-6 * chrono::duration_cast<std::chrono::microseconds>(t - mStart).count();
	}
private:
	chrono::system_clock::time_point mStart;
};

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

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int digScore(int C, int digNum, int adjNum){
    if(adjNum > 2*digNum){
        int m = adjNum%digNum;
        return m * C/3 + (digNum - m) * C/2;
    } else if(adjNum > digNum){
        int m = adjNum%digNum;
        return m * C/2 + (digNum - m) * C;
    }
    return digNum * C;
}

class State {
public:
    explicit State() : mUse(50, 0), mDigNum(0), mAdjCnt(0), mScore(0){}
    inline bool isDig(int x, int y) const {
        return mUse[x]&(1LL<<y);
    }
    bool canRemove(int x, int y){
        if(!isDig(x, y)) return false;
        vector<uint64_t> visit(50, 0ULL);
        queue<int> qu;
        mUse[x] ^= 1LL << y;
        int cnt = 0;
        for(int i=0;i<50;i++){
            if(isDig(0, i)){
                qu.push(i);
                visit[0] |= 1LL << i;
                ++cnt;
            }
            if(isDig(49, i)){
                qu.push(49*64+i);
                visit[49] |= 1LL << i;
                ++cnt;
            }
        }
        for(int i=1;i<49;i++){
            if(isDig(i, 0)){
                qu.push(64*i);
                visit[i] |= 1LL << 0;
                ++cnt;
            }
            if(isDig(i, 49)){
                qu.push(64*i+49);
                visit[i] |= 1LL << 49;
                ++cnt;
            }
        }
        while(!qu.empty()){
            int cx = qu.front()/64, cy = qu.front()%64; qu.pop();
            for(int d=0;d<4;d++){
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if(nx < 0 || 50 <= nx || ny < 0 || 50 <= ny) continue;
                if(!isDig(nx, ny)) continue;
                if(visit[nx]&(1LL<<ny)) continue;
                visit[nx] |= 1LL << ny;
                ++cnt;
                qu.push(64*nx+ny);
            }
        }
        mUse[x] ^= 1LL << y;
        return cnt == mDigNum - 1;
    }
    void remove(int C, const vector<vector<int>>& p, int x, int y){
        assert(isDig(x, y));
        mScore += digScore(C, mDigNum, mAdjCnt);
        for(int d=0;d<4;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx < 0 || 50 <= nx || ny < 0 || 50 <= ny || isDig(nx, ny)){
                --mAdjCnt;
            }
        }
        mUse[x] ^= 1LL << y;
        mScore -= p[x][y];
        --mDigNum;
        mScore -= digScore(C, mDigNum, mAdjCnt);
        verify(C, p);
    }
    bool canStartDig(int x, int y){
        if(isDig(x, y)) return false;
        if(x == 0 || x == 49 || y == 0 || y == 49) return true;
        for(int d=0;d<4;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(isDig(nx, ny)) return true;
        }
        return false;
    }
    void dig(const vector<pair<int, int>>& pts, int C, const vector<vector<int>>& p){
        mScore += digScore(C, mDigNum, mAdjCnt);
        for(auto& [x, y] : pts){
            if(isDig(x, y)) continue;
            mUse[x] |= 1LL << y;
            ++mDigNum;
            mScore += p[x][y];
            for(int d=0;d<4;d++){
                int nx = x + dx[d];
                int ny = y + dy[d];
                if(nx < 0 || 50 <= nx || ny < 0 || 50 <= ny || isDig(nx, ny)) ++mAdjCnt;
            }
        }
        mScore -= digScore(C, mDigNum, mAdjCnt);
        verify(C, p);
    }
    vector<pair<int, int>> makeWay() const {
        vector<vector<int>> used(50, vector<int>(50, 0));
        vector<pair<int, int>> res;
        while(res.size() < mDigNum){
            int bestX = -1, bestY = -1, bestAdj = -1, bestNext = -1;
            for(int x=0;x<50;x++){
                for(int y=0;y<50;y++){
                    if(!isDig(x, y)) continue;
                    if(used[x][y]) continue;
                    int adj = 0, next = 0;
                    for(int d=0;d<4;d++){
                        int nx = x+dx[d];
                        int ny = y+dy[d];
                        if(nx < 0 || 50 <= nx || ny < 0 || 50 <= ny){
                            ++adj;
                            continue;
                        }
                        if(!isDig(nx, ny)) continue;
                        if(used[nx][ny]) ++adj;
                        else ++next;
                    }
                    if(adj > bestAdj || (adj == bestAdj && next > bestNext)){
                        bestX = x;
                        bestY = y;
                        bestAdj = adj;
                        bestNext = next;
                    }
                }
            }
            assert(bestX != -1);
            res.emplace_back(bestX, bestY);
            used[bestX][bestY] = 1;
        }
        return res;
    }
    const vector<uint64_t>& getUse() const { return mUse; }
    int getScore() const { return mScore; }
    void verify(int C, const vector<vector<int>>& p){
        return;
        int adj = 0, num = 0;
        for(int i=0;i<50;i++){
            for(int j=0;j<50;j++){
                if(isDig(i, j)){
                    ++num;
                    if(i==0) ++adj;
                    if(j==0) ++adj;
                    if(i == 49 || isDig(i+1, j)) ++adj;
                    if(j == 49 || isDig(i, j+1)) ++adj;
                }
            }
        }
        assert(num == mDigNum);
        assert(adj == mAdjCnt);
        vector<vector<int>> visit(50, vector<int>(50, 0));
        queue<pair<int, int>> qu;
        int vcnt = 0;
        for(int i=0;i<50;i++){
            if(isDig(0, i)){
                qu.emplace(0, i);
                visit[0][i] = 1;
                ++vcnt;
            }
            if(isDig(49, i)){
                qu.emplace(49, i);
                visit[49][i] = 1;
                ++vcnt;
            }
        }
        for(int i=1;i<49;i++){
            if(isDig(i, 0)){
                qu.emplace(i, 0);
                visit[i][0] = 1;
                ++vcnt;
            }
            if(isDig(i, 49)){
                qu.emplace(i, 49);
                visit[i][49] = 1;
                ++vcnt;
            }
        }
        while(!qu.empty()){
            auto& [cx, cy] = qu.front(); qu.pop();
            for(int d=0;d<4;d++){
                int nx = cx+dx[d];
                int ny = cy+dy[d];
                if(nx < 0 || 50 <= nx || ny < 0 || 50 <= ny || !isDig(nx, ny) || visit[nx][ny]) continue;
                visit[nx][ny] = 1;
                ++vcnt;
                qu.emplace(nx, ny);
            }
        }
        assert(vcnt == mDigNum);
        int score = -digScore(C, mDigNum, mAdjCnt);
        for(int i=0;i<50;i++){
            for(int j=0;j<50;j++){
                if(isDig(i, j)) score += p[i][j];
            }
        }
        assert(score == mScore);
    }
private:
    vector<uint64_t> mUse;
    int mDigNum;
    int mAdjCnt;
    int mScore;
};

double highTemp = 4.979906972778812;
double lowTemp = 0.04497702913927723;
double tempMove = 0.864176222096778;
int ITER = 10000;

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

vector<pair<int, int>> greedy(int C, const vector<vector<int>>& p){
    auto cost = p;
    for(auto& v: cost){
        for(auto& t : v) t -= C;
    }
    vector<vector<int>> use(50, vector<int>(50, 0));
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            if(cost[i][j] > 0){
                use[i][j] = 1;
            }
        }
    }
    while(true){
        UnionFind uf(64*50);
        const int r = 64*50-1;
        for(int i=0;i<50;i++){
            for(int j=0;j<50;j++){
                if(use[i][j] && 0 < i && i < 49 && 0 < j && j < 49){
                    if(use[i-1][j]) uf.merge(64*i+j, 64*(i-1)+j);
                    if(use[i+1][j]) uf.merge(64*i+j, 64*(i+1)+j);
                    if(use[i][j-1]) uf.merge(64*i+j, 64*i+j-1);
                    if(use[i][j+1]) uf.merge(64*i+j, 64*i+j+1);
                } else {
                    uf.merge(64*i+j, r);
                }
            }
        }
        if(uf.getSize(uf.getRoot(r)) == 2501) break;
        vector<vector<int>> visit(50, vector<int>(50, 0));
        vector<vector<int>> dist(50, vector<int>(50, -1000000000));
        vector<vector<pair<int, int>>> prev(50, vector<pair<int, int>>(50, make_pair(-1, -1)));
        priority_queue<pair<int, pair<int, int>>> qu;
        for(int i=0;i<50;i++){
            for(int j=0;j<50;j++){
                if(use[i][j] && uf.same(64*i+j, r)){
                    dist[i][j] = 0;
                    visit[i][j] = 1;
                    qu.emplace(dist[i][j], make_pair(i, j));
                } else if(i==0 || i==49 || j==0 || j==49){
                    dist[i][j] = cost[i][j];
                    qu.emplace(dist[i][j], make_pair(i, j));
                    visit[i][j] = 1;
                }
            }
        }
        while(!qu.empty()){
            auto pr = qu.top(); qu.pop();
            bool ok = false;
            for(int i=0;i<4;i++){
                int nx = pr.second.first + dx[i];
                int ny = pr.second.second + dy[i];
                if(nx < 0 || 50 <= nx || ny < 0 || 50 <= ny) continue;
                if(use[nx][ny] && dist[nx][ny] == -1000000000){
                    ok = true;
                    int x = pr.second.first, y = pr.second.second;
                    while(x >= 0){
                        use[x][y] = 1;
                        auto pre = prev[x][y];
                        x = pre.first;
                        y = pre.second;
                    }
                } else if(!visit[nx][ny]){
                    dist[nx][ny] = pr.first + cost[nx][ny];
                    prev[nx][ny] = pr.second;
                    qu.emplace(dist[nx][ny], make_pair(nx, ny));
                    visit[nx][ny] = 1;
                }
            }
            if(ok) break;
        }
    }
    vector<pair<int, int>> res;
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++) if(use[i][j]) res.emplace_back(i, j);
    }
    return res;
}

vector<pair<int, int>> anneal(int C, const vector<vector<int>>& p){
    XorShift gen(1000000007);
    State curState = State();
    curState.dig(greedy(C, p), C, p);
    State bestState = curState;
    int curBest = curState.getScore();
    int curScore = curState.getScore();
    auto typeGen = uniform_int_distribution<int>(0, 1);
    auto outerGen = uniform_int_distribution<int>(0, 49);
    auto dirGen = uniform_int_distribution<int>(0, 3);
    auto digGen = uniform_int_distribution<int>(1, 10);
    auto probGen = uniform_real_distribution<>(0.0, 1.0);
    Timer timer;
    const double timeLimit = 1.8;
    int rep = 0;
    while(timer.sec() < timeLimit){
        const double curTemp = highTemp + pow(timer.sec()/timeLimit, tempMove) * (lowTemp - highTemp);
        for(int _=0;_<ITER;_++){
            ++rep;
            if(typeGen(gen) != 0){
                int a = outerGen(gen);
                int b = outerGen(gen);
                while(!curState.canStartDig(a, b)){
                    a = outerGen(gen);
                    b = outerGen(gen);
                }
                State nextState = curState;
                int digNum = digGen(gen);
                vector<pair<int, int>> pts;
                pts.emplace_back(a, b);
                while(pts.size() < digNum){
                    int dir = dirGen(gen);
                    int na = a + dx[dir];
                    int nb = b + dy[dir];
                    if(na < 0 || 50 <= na || nb < 0 || 50 <= nb) continue;
                    if(pts.size() >= 2 && pts[pts.size()-2].first == na && pts[pts.size()-2].second == nb) continue;
                    a = na; b = nb;
                    pts.emplace_back(a, b);
                }
                nextState.dig(pts, C, p);
                int newScore = nextState.getScore();
                if(curScore < newScore || probGen(gen) < exp((newScore - curScore)/curTemp)){
                    curScore = newScore;
                    curState = nextState;
                    if(curBest < curScore){
                        curBest = curScore;
                        bestState = nextState;
                    }
                }
            } else {
                int a = outerGen(gen), b = outerGen(gen);
                if(!curState.canRemove(a, b)) continue;
                State nextState = curState;
                nextState.remove(C, p, a, b);
                int newScore = nextState.getScore();
                if(curScore < newScore || probGen(gen) < exp((newScore - curScore)/curTemp)){
                    curScore = newScore;
                    curState = nextState;
                    if(curBest < curScore){
                        curBest = curScore;
                        bestState = nextState;
                    }
                }
            }
        }
    }
    // cout << rep << endl;
    // cout << bestState.getScore() << endl;
    // for(int i=0;i<50;i++){
    //     for(int j=0;j<50;j++) cout << bestState.isDig(i, j); cout << endl;
    // }
    return bestState.makeWay();
}

int main(int argc, char *argv[]){
    if(argc >= 2) highTemp = atof(argv[1]);
    if(argc >= 3) lowTemp = atof(argv[2]);
    if(argc >= 4) tempMove = atof(argv[3]);
    if(argc >= 5) ITER = (int)atof(argv[4]);
    int C; cin >> C;
    vector<vector<int>> p(50, vector<int>(50, 0));
    for(auto& v : p){
        for(auto& t : v) cin >> t;
    }
    auto res = anneal(C, p);
    cout << res.size() << endl;
    for(auto& [x, y] : res) cout << x << " " << y << endl;
}
