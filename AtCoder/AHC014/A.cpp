#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <set>
#include <map>
#include <queue>
#include <array>
#include <cstdio>
#include <cassert>
#include <functional>
#include <random>
#include <numeric>

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
    explicit Action(int x0 = 0, int y0 = 0, int x2 = 0, int y2 = 0, bool diag = false)
        : mAction(x0 | (y0<<6) | (x2 << 12) | (y2 << 18) | (diag ? 1 << 24 : 0))
    {}
    void invalidate(){ mAction = 0; }
    bool isValid() const { return mAction != 0; }
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
    pair<int, int> size() const {
        const int x0 = (mAction)%(1<<6);
        const int y0 = (mAction >> 6)%(1<<6);
        const int x2 = (mAction >> 12)%(1<<6);
        const int y2 = (mAction >> 18)%(1<<6);
        if(mAction&(1<<24)){
            const int a0 = (x0+y0);
            const int b0 = (x0-y0);
            const int a2 = (x2+y2);
            const int b2 = (x2-y2);
            return make_pair(abs(a0-a2)/2, abs(b0-b2)/2);
        }
        return make_pair(abs(x0-x2), abs(y0-y2));
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
    int mAction;
};

//------------------------------------------------------------------------------
// 16 17 18 19 20
// 12 13 14 15
//  8  9 10 11
//  4  5  6  7
//  0  1  2  3

template<int N>
class Board {
public:
    explicit Board()
        : mScore(0)
    {
        fill(mMark.begin(), mMark.end(), 0);
        fill(mUse.begin(), mUse.end(), 0);
        fill(mNext.begin(), mNext.end(), -1);
        initNext();
    }
    bool operator==(const Board& b) const {
        if(mScore != b.mScore) return false;
        if(mMark != b.mMark) return false;
        if(mUse != b.mUse) return false;
        if(mNext != b.mNext) return false;
        vector<long long> src, dst;
        for(auto& a : mActions) src.push_back(a.get());
        for(auto& a : b.mActions) dst.push_back(a.get());
        if(src != dst) return false;
        // if(mActions != b.mActions) return false;
        return true;
    }
    inline void mark(int x, int y){ mMark[y] |= (1LL << x); }
    inline void unmark(int x, int y){ mMark[y] &= ~(1LL << x);}
    inline bool isMark(int x, int y) const { return mMark[y] & (1LL << x); }
    inline int getScore() const { return mScore; }
    const vector<Action>& getActions() const { return mActions; }
    void setActions(const vector<Action>& actions){ mActions = actions; }
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
    inline void resetUse(int idx, int dir){ mUse[idx] &= ~(1<<dir); }
    int getNext(int x, int y, int dir) const {
        return getNext(getIdx(x, y), dir);
    }
    int getNext(int idx, int dir) const {
        if(mNext[8*idx+dir] != -1) return mNext[8*idx+dir];
        const int d[] = {1, N+2, N+1, N, -1, -(N+2), -(N+1), -N};
        idx += d[dir];
        while(0 <= idx && idx <= (N+1)*(N+2)){
            if(mNext[8*idx+(dir^4)] != -1 || outerIdx(idx)){
                return idx;
            }
            idx += d[dir];
        }
        return -1;
    }
    void initNext(){
        mNext[1] = (N+1)*(N+2);
        mNext[8*(N+1)*(N+2)+5] = 0;
        auto init = [&](int idx){
            for(int d=0;d<4;d++){
                int end = getNext(idx, d);
                if(end != -1){
                    mNext[8*idx+d] = end;
                    mNext[8*end+d+4] = idx;
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
            mNext[8*idx+d] = end;
            mNext[8*end+d+4] = idx;
            mNext[8*prev+d] = idx;
            mNext[8*idx+d+4] = prev;
            if(isUse(prev, d)){
                setUse(idx, d);
                setUse(idx, d+4);
            }
        }
        mScore += weight(x, y);
    }
    void removePoint(int x, int y){
        if(!isMark(x, y)) return;
        unmark(x, y);
        const int idx = getIdx(x, y);
        for (int d = 0; d < 4; d++)
        {
            const int end = getNext(idx, d);
            const int prev = getNext(idx, d+4);
            mNext[8*prev+d] = end;
            mNext[8*end+d+4] = prev;
            mNext[8*idx+d] = -1;
            mNext[8*idx+d+4] = -1;
            if(isUse(idx, d)){
                resetUse(idx, d);
                resetUse(idx, d+4);
            }
        }
        mScore -= weight(x, y);
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
        for(int i=0;i<2;i++){
            int d = calcDir(x[i], y[i], x[(i+1)%4], y[(i+1)%4]);
            setUse(idx[i], d);
            setUse(idx[(i+1)%4], (d+4)%8);
            setUse(idx[(i+3)%4], d);
            setUse(idx[(i+2)%4], (d+4)%8);
        }
        mActions.push_back(action);
    }
    void undoAction(){
        if(mActions.empty()) return;
        undoActionImpl_(mActions.back());
        mActions.pop_back();
    }
    void removeInvalidAction(){
        int sz = mActions.size();
        int back = 0;
        int invalid = 0;
        for(int i=0;i<sz;i++){
            if(!mActions[i].isValid()){ ++invalid; continue; }
            if(i != back){
                mActions[back] = mActions[i];
            }
            ++back;
        }
        mActions.resize(back);
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
    vector<Action> showAllActionDiff(const vector<Action>& prevActions, const Action& curAction) const {
        vector<Action> res;
        res.reserve(prevActions.size());

        auto checkBoth = [&](int x0, int y0, int x1, int y1, int idx0, int idx1, int dir){
            if(isUse(idx0, dir)) return false;
            if(isUse(idx1, (dir+4)%8)) return false;
            if(getNext(idx0, dir) != idx1) return false;
            if(getNext(idx1, (dir+4)%8) != idx0) return false;
            return true;
        };

        auto checkOne = [&](int x0, int y0, int x1, int y1, int idx0, int idx1, int dir){
            if(isUse(idx1, (dir+4)%8)) return false;
            int prev = getNext(idx1, (dir+4)%8);
            return min(prev, idx1) < idx0 && idx0 < max(prev, idx1);
        };

        for(const auto& a : prevActions){
            const auto b = a.get();
            const int x[] = {int(b % (1 << 6)), int((b >> 12) % (1 << 6)), int((b >> 24) % (1 << 6)), int((b >> 36) % (1 << 6))};
            const int y[] = {int((b >> 6) % (1 << 6)), int((b >> 18) % (1 << 6)), int((b >> 30) % (1 << 6)), int((b >> 42) % (1 << 6))};
            const int idx[] = {getIdx(x[0], y[0]), getIdx(x[1], y[1]), getIdx(x[2], y[2]), getIdx(x[3], y[3])};
            const int dir12 = calcDir(x[1], y[1], x[2], y[2]);
            if(!checkBoth(x[1], y[1], x[2], y[2], idx[1], idx[2], dir12)) continue;
            const int dir32 = calcDir(x[3], y[3], x[2], y[2]);
            if(!checkBoth(x[3], y[3], x[2], y[2], idx[3], idx[2], dir32)) continue;
            if(!checkOne(x[0], y[0], x[1], y[1], idx[0], idx[1], dir32)) continue;
            if(!checkOne(x[0], y[0], x[3], y[3], idx[0], idx[3], dir12)) continue;
            res.push_back(a);
        }
        const auto b = curAction.get();
        const int x0 = int(b % (1 << 6));
        const int y0 = int((b >> 6) % (1 << 6));
        const int idx0 = getIdx(x0, y0);
        int outer = 0;
        for(int i=0;i<8;i++){
            if(isUse(idx0, i) || outerIdx(getNext(idx0, i))) outer |= (1 << i);
        }
        for(int i=0;i<8;i++){
            if(outer&(1<<i)) continue;
            int idx1 = getNext(idx0, i);
            if(!(outer&(1<<((i+2)%8)))){
                int idx3 = getNext(idx0, (i+2)%8);
                validateAction_(res, idx0, idx1, idx3, (i+2)%8, i);
            }
            for(int j=2;j<=6;j+=4){
                if(isUse(idx1, (i+j)%8)) continue;
                int idx2 = getNext(idx1, (i+j)%8);
                if(outerIdx(idx2)) continue;
                validateAction_(res, idx1, idx2, idx0, (i+4)%8, (i+j)%8);
            }
        }
        return res;
    }
private:
    void checkOneDir_(vector<Action>& res, int startIdx, int dir, int endIdx = -1) const {
        int cur = getNext(startIdx, dir);
        if(outerIdx(cur)) return;
        while(cur != endIdx){
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
    void undoActionImpl_(const Action& action){
        const auto b = action.get();
        const int x[] = {int(b % (1 << 6)), int((b >> 12) % (1 << 6)), int((b >> 24) % (1 << 6)), int((b >> 36) % (1 << 6))};
        const int y[] = {int((b >> 6) % (1 << 6)), int((b >> 18) % (1 << 6)), int((b >> 30) % (1 << 6)), int((b >> 42) % (1 << 6))};
        const int idx[] = {getIdx(x[0], y[0]), getIdx(x[1], y[1]), getIdx(x[2], y[2]), getIdx(x[3], y[3])};
        assert(isMark(x[0], y[0]));
        assert(isMark(x[1], y[1]));
        assert(isMark(x[2], y[2]));
        assert(isMark(x[3], y[3]));
        removePoint(x[0], y[0]);
        for (int i=0;i<2;i++){
            int d = calcDir(x[i], y[i], x[(i+1)%4], y[(i+1)%4]);
            resetUse(idx[i], d);
            resetUse(idx[(i+1)%4], (d+4)%8);
            resetUse(idx[(i+3)%4], d);
            resetUse(idx[(i+2)%4], (d+4)%8);
        }
    }
private:
    int mScore;
    array<long long, N> mMark;
    array<unsigned char, (N+1)*(N+1)> mUse;
    array<int, 8*((N+1)*(N+2)+1)> mNext;
    vector<Action> mActions;
};

//------------------------------------------------------------------------------
template<int N>
void run(int argc, const char* argv[], int M){
    Timer timer;

    const double weight_mul = 0.21747960999756752;
    const double weight_add = 0.025718087042180687;
    const double initial_temp = 0.43462030983794153;
    const double final_temp = 0.06616166063711515;
    const int first_time_limit = 1000;
    const int second_time_limit = 4900;

    // if(argc >= 2) weight_mul = atof(argv[1]);
    // if(argc >= 3) weight_add = atof(argv[2]);
    // if(argc >= 4) initial_temp = atof(argv[3]);
    // if(argc >= 5) final_temp = atof(argv[4]);

    Board<N> board;
    for(int i=0;i<M;i++){
        int x, y; cin >> x >> y;
        board.putPoint(x, y);
    }
    int bestScore = 0;
    vector<Action> bestAction;
    XorShift rnd(141421356UL);
    int S = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) S += Board<N>::weight(i, j);
    }
    int cnt = 0;
    while(timer.msec() < first_time_limit){
        ++cnt;
        auto& curBoard = board;
        auto actions = curBoard.showAllAction();
        while(!actions.empty()){
            vector<double> prob(actions.size());
            for(int i=0;i<(int)actions.size();i++){
                auto sz = actions[i].size();
                prob[i] = 1.0/(weight_mul*sz.first*sz.second+weight_add*(sz.first+sz.second));
            }
            double sum = accumulate(prob.begin(), prob.end(), 0.0);
            double p = uniform_real_distribution<double>(0.0, sum)(rnd);
            int idx = actions.size() - 1;
            for(int i=0;i<(int)actions.size()-1;i++){
                p -= prob[i];
                if(p < 0){ idx = i; break; }
            }
            curBoard.doAction(actions[idx]);
            actions = curBoard.showAllActionDiff(actions, actions[idx]);
        }
        if(bestScore < curBoard.getScore()){
            bestScore = curBoard.getScore();
            bestAction = curBoard.getActions();
            cerr << "best: " << int(1e6 * N * N / M * bestScore / S + 0.5) << endl;
        }
        while(!curBoard.getActions().empty()) curBoard.undoAction();
    }
    cerr << cnt << endl;
    cnt = 0;

    vector<long long> removedPos(61, 0LL);
    int finalScore = bestScore;
    auto finalAction = bestAction;
    while(timer.msec() < second_time_limit){
        ++cnt;
        auto& curBoard = board;
        int removeIdx = -1;
        if(!bestAction.empty()){

            int idx = removeIdx = rnd()%bestAction.size();
            fill(removedPos.begin(), removedPos.end(), 0LL);
            {
                const int n = curBoard.getActions().size();
                if(idx < n){
                    for(int i=idx;i<n;i++){
                        curBoard.undoAction();
                    }
                } else if(n < idx){
                    for(int i=n;i<idx;i++){
                        curBoard.doAction(bestAction[i]);
                    }
                }
            }
            {
                const auto b = bestAction[idx].get();
                const int x = b%(1<<6);
                const int y = (b>>6)%(1<<6);
                removedPos[y] |= 1LL << x;
            }
            for(int i=idx+1;i<(int)bestAction.size();i++){
                const auto b = bestAction[i].get();
                const int x[] = {int(b%(1<<6)), int((b>>12)%(1<<6)), int((b>>24)%(1<<6)), int((b>>36)%(1<<6))};
                const int y[] = {int((b>>6)%(1<<6)), int((b>>18)%(1<<6)), int((b>>30)%(1<<6)), int((b>>42)%(1<<6))};
                bool ok = true;
                for(int j=0;j<4;j++){
                    if(removedPos[y[j]]&(1LL<<x[j])){
                        ok = false;
                        break;
                    }
                }
                if(ok){
                    curBoard.doAction(bestAction[i]);
                } else {
                    removedPos[y[0]] |= 1LL << x[0];
                }
            }
        }
        auto actions = curBoard.showAllAction();
        while(!actions.empty()){
            vector<double> prob(actions.size());
            for(int i=0;i<(int)actions.size();i++){
                auto sz = actions[i].size();
                prob[i] = 1.0/(weight_mul*sz.first*sz.second+weight_add*(sz.first+sz.second));
            }
            double sum = accumulate(prob.begin(), prob.end(), 0.0);
            double p = uniform_real_distribution<double>(0.0, sum)(rnd);
            int idx = actions.size() - 1;
            for(int i=0;i<(int)actions.size()-1;i++){
                p -= prob[i];
                if(p < 0){ idx = i; break; }
            }
            curBoard.doAction(actions[idx]);
            actions = curBoard.showAllActionDiff(actions, actions[idx]);
        }
        const double ratio = (timer.msec() - first_time_limit) / (second_time_limit - first_time_limit);
        const double rev_ratio = 1 - ratio;
        const double temperature = initial_temp + (final_temp - initial_temp) * (1 - rev_ratio * rev_ratio * rev_ratio);
        double delta = 1e-5 * (int(1e6 * N * N / M * curBoard.getScore() / S + 0.5) - int(1e6 * N * N / M * bestScore / S + 0.5));
        if(delta > 0 || bernoulli_distribution(exp(delta/temperature))(rnd)){
            bestScore = curBoard.getScore();
            bestAction = curBoard.getActions();
            if(finalScore < bestScore){
                finalScore = bestScore;
                finalAction = bestAction;
                cerr << "best: " << int(1e6 * N * N / M * bestScore / S + 0.5) << endl;
            }
        } else if(removeIdx != -1){
            const int n = curBoard.getActions().size();
            for(int i=removeIdx;i<n;i++){
                curBoard.undoAction();
            }
        }
    }

    cerr << cnt << endl;

    cout << finalAction.size() << endl;
    for(const auto& a : finalAction){
        a.print();
    }
    cerr << int(1e6 * N * N / M * finalScore / S + 0.5) << endl;

}

//------------------------------------------------------------------------------
int main(int argc, const char* argv[]){
    Timer timer;
    int N, M; cin >> N >> M;
    if(N == 31){
        run<31>(argc, argv, M);
    } else if(N == 33){
        run<33>(argc, argv, M);
    } else if(N == 35){
        run<35>(argc, argv, M);
    } else if(N == 37){
        run<37>(argc, argv, M);
    } else if(N == 39){
        run<39>(argc, argv, M);
    } else if(N == 41){
        run<41>(argc, argv, M);
    } else if(N == 43){
        run<43>(argc, argv, M);
    } else if(N == 45){
        run<45>(argc, argv, M);
    } else if(N == 47){
        run<47>(argc, argv, M);
    } else if(N == 49){
        run<49>(argc, argv, M);
    } else if(N == 51){
        run<51>(argc, argv, M);
    } else if(N == 53){
        run<53>(argc, argv, M);
    } else if(N == 55){
        run<55>(argc, argv, M);
    } else if(N == 57){
        run<57>(argc, argv, M);
    } else if(N == 59){
        run<59>(argc, argv, M);
    } else if(N == 61){
        run<61>(argc, argv, M);
    } else {
        cout << 0 << endl;
    }
}
