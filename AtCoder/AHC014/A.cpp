#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <queue>
#include <array>
#include <cstdio>
#include <cassert>

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
};

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
// Dir
//     2
//   3   1
// 4   *   0
//   5   7
//     6
int calcDir(int x0, int y0, int x1, int y1){
    if(y0 == y1){
        return x0 < x1 ? 0 : 4;
    }
    if(x0 == x1){
        return y0 < y1 ? 2 : 6;
    }
    if(x0-y0 == x1-y1){
        return x0 < x1 ? 1 : 5;
    }
    return y0 < y1 ? 3 : 7;
}

//------------------------------------------------------------------------------
class Action {
public:
    explicit Action(int x0, int y0, int x2, int y2, bool diag)
        : mAction(x0 | (y0<<6) | (x2 << 12) | (y2 << 18) | (diag ? 1 << 24 : 0))
    {}
    long long get() const {
        const long long x0 = (mAction)%(1<<6);
        const long long y0 = (mAction >> 6)%(1<<6);
        const long long x2 = (mAction >> 12)%(1<<6);
        const long long y2 = (mAction >> 18)%(1<<6);
        if(mAction&(1<<24)){
            const long long a0 = (x0+y0);
            const long long b0 = (x0-y0);
            const long long a2 = (x2+y2);
            const long long b2 = (x2-y2);
            const long long x1 = (a0+b2)/2;
            const long long y1 = (a0-b2)/2;
            const long long x3 = (a2+b0)/2;
            const long long y3 = (a2-b0)/2;
            return (x0)|(y0<<6)|(x1<<12)|(y1<<18)|(x2<<24)|(y2<<30)|(x3<<36)|(y3<<42);
        }
        return (x0)|(y0<<6)|(x0<<12)|(y2<<18)|(x2<<24)|(y2<<30)|(x2<<36)|(y0<<42);
    }
    void print() const {
        long long b = get();
        cout << (b%(1<<6));
        b /= (1<<6);
        for(int i=1;i<8;i++){
            cout << " " << (b%(1<<6));
            b /= (1<<6);
        }
        cout << endl;
    }
private:
    const int mAction;
};

//------------------------------------------------------------------------------
// 16 17 18 19 20
// 12 13 14 15
//  8  9 10 11
//  4  5  6  7
//  0  1  2  3

int N;

class Board {
public:
    explicit Board()
        : mScore(0)
        , mMark(N, 0)
        , mUse((N+1)*(N+1), 0)
        , mNext((N+1)*(N+2)+1, vector<int>(8, -1))
    {
        initNext();
    }
    inline void mark(int x, int y){ mMark[y] |= (1LL << x); }
    inline bool isMark(int x, int y) const { return mMark[y] & (1LL << x); }
    inline int getScore() const { return mScore; }
    const vector<Action>& getActions() const { return mActions; }
    static int getIdx(int x, int y){ return (N+1)*(y+1) + x+1; }
    static inline bool outerIdx(int idx){ return idx <= N+1 || (N+1)*(N+1) <= idx || idx%(N+1) == 0; }
    static int getX(int idx){ return idx%(N+1) - 1; }
    static int getY(int idx){ return idx/(N+1) - 1; }
    static int weight(int x, int y){
        const int dx = x - N/2;
        const int dy = y - N/2;
        return dx * dx + dy * dy + 1;
    }
    inline bool isUse(int x, int y, int dir) const { return isUse(getIdx(x, y), dir); }
    inline bool isUse(int idx, int dir) const { return idx < mUse.size() && mUse[idx]&(1<<dir); }
    inline void setUse(int x, int y, int dir){ setUse(getIdx(x, y), dir); }
    inline void setUse(int idx, int dir){ mUse[idx] |= 1<<dir; }
    int getNext(int x, int y, int dir) const {
        return getNext(getIdx(x, y), dir);
    }
    int getNext(int idx, int dir) const {
        if(mNext[idx][dir] != -1) return mNext[idx][dir];
        const int d[] = {1, N+2, N+1, N, -1, -(N+2), -(N+1), -N};
        idx += d[dir];
        while(0 <= idx && idx <= (N+1)*(N+2)){
            if(mNext[idx][dir^4] != -1 || outerIdx(idx)){
                return idx;
            }
            idx += d[dir];
        }
        return -1;
    }
    void initNext(){
        mNext[0][1] = (N+1)*(N+2);
        mNext[(N+1)*(N+2)][5] = 0;
        auto init = [&](int idx){
            for(int d=0;d<4;d++){
                int end = getNext(idx, d);
                if(end != -1){
                    mNext[idx][d] = end;
                    mNext[end][d+4] = idx;
                }
            }
        };
        for(int i=1;i<=N;i++) init(i);
        for(int i=N+1;i<=(N+1)*(N+1);i+=N+1) init(i);
    }
    void putPoint(int x, int y){
        if(isMark(x, y)) return;
        mark(x, y);
        const int idx = getIdx(x, y);
        for(int d=0;d<4;d++){
            const int end = getNext(idx, d);
            const int prev = getNext(end, d+4);
            mNext[idx][d] = end;
            mNext[end][d+4] = idx;
            mNext[prev][d] = idx;
            mNext[idx][d+4] = prev;
            if(isUse(prev, d)){
                setUse(idx, d);
                setUse(idx, d+4);
            }
        }
        mScore += weight(x, y);
    }
    void doAction(const Action& action){
        const auto b = action.get();
        const int x[] = {int(b%(1<<6)), int((b>>12)%(1<<6)), int((b>>24)%(1<<6)), int((b>>36)%(1<<6))};
        const int y[] = {int((b>>6)%(1<<6)), int((b>>18)%(1<<6)), int((b>>30)%(1<<6)), int((b>>42)%(1<<6))};
        const int idx[] = {getIdx(x[0], y[0]), getIdx(x[1], y[1]), getIdx(x[2], y[2]), getIdx(x[3], y[3])};
        assert(!isMark(x[0], y[0]));
        assert(isMark(x[1], y[1]));
        assert(isMark(x[2], y[2]));
        assert(isMark(x[3], y[3]));
        putPoint(x[0], y[0]);
        for(int i=0;i<4;i++){
            int d = calcDir(x[i], y[i], x[(i+1)%4], y[(i+1)%4]);
            setUse(idx[i], d);
            setUse(idx[(i+1)%4], (d+4)%8);
        }
        mActions.push_back(action);
    }
    vector<Action> showAllAction() const {
        vector<Action> res;
        for(int i=0;i<=N;i++) checkOneDir_(res, i, 1);
        for(int i=N+1;i<=(N+1)*(N+1);i+=N+1){
            checkOneDir_(res, i, 0);
            checkOneDir_(res, i, 1);
        }
        return res;
    }
private:
    void checkOneDir_(vector<Action>& res, int startIdx, int dir) const {
        int cur = getNext(startIdx, dir);
        if(outerIdx(cur)) return;
        while(true){
            int next = getNext(cur, dir);
            if(outerIdx(next)) return;
            if(!isUse(cur, dir)){
                if(!isUse(cur, (dir+2%8))){
                    int p3 = getNext(cur, (dir+2)%8);
                    if(!outerIdx(p3)){
                        validateAction_(res, cur, next, p3, (dir+2)%8, dir);
                    }
                }
                if(!isUse(cur, (dir+6%8))){
                    int p3 = getNext(cur, (dir+6)%8);
                    if(!outerIdx(p3)){
                        validateAction_(res, cur, next, p3, (dir+6)%8, dir);
                    }
                }
                if(!isUse(next, (dir+2%8))){
                    int p3 = getNext(next, (dir+2)%8);
                    if(!outerIdx(p3)){
                        validateAction_(res, next, cur, p3, (dir+2)%8, dir^4);
                    }
                }
                if(!isUse(next, (dir+6%8))){
                    int p3 = getNext(next, (dir+6)%8);
                    if(!outerIdx(p3)){
                        validateAction_(res, next, cur, p3, (dir+6)%8, dir^4);
                    }
                }
            }
            cur = next;
        }
    }
    //
    //     d32
    //   3 --> *
    //         ^
    //         | d12
    //   0     1
    //
    void validateAction_(vector<Action>& res, int idx0, int idx1, int idx3, int dir12, int dir32) const {
        if(isUse(idx1, dir12)) return;
        if(isUse(idx3, dir32)) return;
        const int idx2 = idx3 + idx1 - idx0;
        const int next1 = getNext(idx1, dir12);
        if(min(idx1, idx2) < next1 && next1 < max(idx1, idx2)) return;
        const int next3 = getNext(idx3, dir32);
        if(min(idx3, idx2) <= next3 && next3 <= max(idx3, idx2)) return;
        res.emplace_back(getX(idx2), getY(idx2), getX(idx0), getY(idx0), dir12%2);
    }
private:
    int mScore;
    vector<long long> mMark;
    vector<unsigned char> mUse;
    vector<vector<int>> mNext;
    vector<Action> mActions;
};

//------------------------------------------------------------------------------
int main(){
    int M; cin >> N >> M;
    Board board;
    for(int i=0;i<M;i++){
        int x, y; cin >> x >> y;
        board.putPoint(x, y);
    }
    XorShift rnd(141421356UL);
    while(true){
        auto actions = board.showAllAction();
        if(actions.empty()) break;
        board.doAction(actions[rnd()%actions.size()]);
    }
    const auto& result = board.getActions();
    cout << result.size() << endl;
    for(const auto& a : result){
        a.print();
    }
}
