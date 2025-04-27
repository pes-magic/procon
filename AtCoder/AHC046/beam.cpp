#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define NDEBUG

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <random>
#include <queue>

using namespace std;

namespace atcoder
{

    namespace internal
    {

        // @return same with std::bit::bit_ceil
        unsigned int bit_ceil(unsigned int n)
        {
            unsigned int x = 1;
            while (x < (unsigned int)(n))
                x *= 2;
            return x;
        }

        // @param n `1 <= n`
        // @return same with std::bit::countr_zero
        int countr_zero(unsigned int n)
        {
#ifdef _MSC_VER
            unsigned long index;
            _BitScanForward(&index, n);
            return index;
#else
            return __builtin_ctz(n);
#endif
        }

        // @param n `1 <= n`
        // @return same with std::bit::countr_zero
        constexpr int countr_zero_constexpr(unsigned int n)
        {
            int x = 0;
            while (!(n & (1 << x)))
                x++;
            return x;
        }

    } // namespace internal

    template <class S, auto op, auto e>
    struct segtree
    {
        static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                      "op must work as S(S, S)");
        static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                      "e must work as S()");

    public:
        segtree() : segtree(0) {}
        explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
        explicit segtree(const std::vector<S> &v) : _n(int(v.size()))
        {
            size = (int)internal::bit_ceil((unsigned int)(_n));
            log = internal::countr_zero((unsigned int)size);
            d = std::vector<S>(2 * size, e());
            for (int i = 0; i < _n; i++)
                d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--)
            {
                update(i);
            }
        }

        void set(int p, S x)
        {
            assert(0 <= p && p < _n);
            p += size;
            d[p] = x;
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }

        S get(int p) const
        {
            assert(0 <= p && p < _n);
            return d[p + size];
        }

        S prod(int l, int r) const
        {
            assert(0 <= l && l <= r && r <= _n);
            S sml = e(), smr = e();
            l += size;
            r += size;

            while (l < r)
            {
                if (l & 1)
                    sml = op(sml, d[l++]);
                if (r & 1)
                    smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }
            return op(sml, smr);
        }

        S all_prod() const { return d[1]; }

        template <bool (*f)(S)>
        int max_right(int l) const
        {
            return max_right(l, [](S x)
                             { return f(x); });
        }
        template <class F>
        int max_right(int l, F f) const
        {
            assert(0 <= l && l <= _n);
            assert(f(e()));
            if (l == _n)
                return _n;
            l += size;
            S sm = e();
            do
            {
                while (l % 2 == 0)
                    l >>= 1;
                if (!f(op(sm, d[l])))
                {
                    while (l < size)
                    {
                        l = (2 * l);
                        if (f(op(sm, d[l])))
                        {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }

        template <bool (*f)(S)>
        int min_left(int r) const
        {
            return min_left(r, [](S x)
                            { return f(x); });
        }
        template <class F>
        int min_left(int r, F f) const
        {
            assert(0 <= r && r <= _n);
            assert(f(e()));
            if (r == 0)
                return 0;
            r += size;
            S sm = e();
            do
            {
                r--;
                while (r > 1 && (r % 2))
                    r >>= 1;
                if (!f(op(d[r], sm)))
                {
                    while (r < size)
                    {
                        r = (2 * r + 1);
                        if (f(op(d[r], sm)))
                        {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    };

} // namespace atcoder

vector<int> X;
vector<int> Y;
static uint64_t Z[20 * 20];
void init_zobrist()
{
    std::mt19937_64 rng(123456789);
    for (int i = 0; i < 20 * 20; i++)
    {
        Z[i] = rng()%(1LL << 48);
    }
}

struct Input
{
    int N;
    int M;
    vector<pair<int, int>> target;
    void input()
    {
        cin >> N >> M;
        for(int i = 0; i < M; i++)
        {
            int x, y;
            cin >> x >> y;
            target.emplace_back(x, y);
        }
        init_zobrist();
    }
};

//------------------------------------------------------------------------------
class Timer
{
public:
    explicit Timer()
        : mStart(chrono::system_clock::now())
    {
    }
    void start() { mStart = chrono::system_clock::now(); }
    double msec() const
    {
        auto t = chrono::system_clock::now();
        return 1e-3 * chrono::duration_cast<std::chrono::microseconds>(t - mStart).count();
    }

private:
    chrono::system_clock::time_point mStart;
};

bool debug = false;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

vector<vector<vector<int>>> genWapp(int N, const vector<int>& board) {
    vector<vector<vector<int>>> warp(4, vector<vector<int>>(board.size(), vector<int>(board.size(), 0)));
    // down
    for(int i=0;i<N;i++){
        int t = N-1;
        for(int j=N-1;j>=0;j--){
            if(board[j] & (1 << i)){
                t = j-1;
            }
            warp[0][j][i] = t;
        }
    }
    // right
    for(int i=0;i<N;i++){
        int t = N-1;
        for(int j=N-1;j>=0;j--){
            if(board[i] & (1 << j)){
                t = j-1;
            }
            warp[1][i][j] = t;
        }
    }
    // up
    for(int i=0;i<N;i++){
        int t = 0;
        for(int j=0;j<N;j++){
            if(board[j] & (1 << i)){
                t = j+1;
            }
            warp[2][j][i] = t;
        }
    }
    // left
    for(int i=0;i<N;i++){
        int t = 0;
        for(int j=0;j<N;j++){
            if(board[i] & (1 << j)){
                t = j+1;
            }
            warp[3][i][j] = t;
        }
    }

    return warp;
}

#include <unordered_map>

unordered_map<uint64_t, int> memo;
int cnt = 0;
int call = 0;

int minCost(uint64_t hash, int x, int y, int step, const vector<pair<int, int>>& target, const vector<int>& board, const vector<vector<vector<int>>>& warp) {
    ++call;
    if(memo.count(hash)){ ++cnt; return memo[hash]; }
    int N = board.size();
    int cost = 0;
    vector<vector<int>> dist(N, vector<int>(N, 1000000));
    for(int s=step+1;s<target.size();s++){
        for(auto& v : dist){
            fill(v.begin(), v.end(), 1000000);
        }
        dist[x][y] = 0;
        queue<pair<int, int>> qu;
        qu.emplace(x, y);
        while(!qu.empty()){
            auto [cx, cy] = qu.front();
            if(cx == target[s].first && cy == target[s].second){
                x = cx;
                y = cy;
                cost += dist[cx][cy];
                break;
            }
            qu.pop();
            for(int d=0;d<4;d++){
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if(board[nx] & (1 << ny)) continue;
                if(dist[nx][ny] > dist[cx][cy] + 1){
                    dist[nx][ny] = dist[cx][cy] + 1;
                    qu.emplace(nx, ny);
                }
            }
            for(int d=0;d<4;d++){
                int nx = d%2 == 0 ? warp[d][cx][cy] : cx;
                int ny = d%2 == 1 ? warp[d][cx][cy] : cy;
                if(dist[nx][ny] > dist[cx][cy]){
                    dist[nx][ny] = dist[cx][cy] + 1;
                    qu.emplace(nx, ny);
                }
            }
        }
        if(x != target[s].first || y != target[s].second){
            return memo[hash] = 1000000;
        }
    }
    return memo[hash] = cost;
}

int minCost(uint64_t hash, int x, int y, int step, const vector<pair<int, int>>& target, const vector<int>& board) {
    if(memo.count(hash)){ ++cnt; return memo[hash]; }
    int N = board.size();
    auto warp = genWapp(N, board);
    return minCost(hash, x, y, step, target, board, warp);
}

//------------------------------------------------------------------------------
class XorShift
{
public:
    using result_type = uint32_t;
    explicit XorShift(result_type seed) { init(seed); }
    void init(result_type s)
    {
        x = 1812433253U * (s ^ (s >> 30));
        y = 1812433253U * (x ^ (x >> 30)) + 1;
        z = 1812433253U * (y ^ (y >> 30)) + 2;
        w = 1812433253U * (z ^ (z >> 30)) + 3;
    }
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    result_type operator()()
    {
        result_type t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

private:
    result_type x;
    result_type y;
    result_type z;
    result_type w;
};

XorShift rnd(1234567891);



namespace beam_search
{

    // ビームサーチの設定
    struct Config
    {
        int max_turn;
        size_t beam_width;
        size_t tour_capacity;
        uint32_t hash_map_capacity;
    };

    // 連想配列
    // Keyにハッシュ関数を適用しない
    // open addressing with linear probing
    // unordered_mapよりも速い
    // nは格納する要素数よりも16倍ほど大きくする
    template <class Key, class T>
    struct HashMap
    {
    public:
        explicit HashMap(uint32_t n)
        {
            if (n % 2 == 0)
            {
                ++n;
            }
            n_ = n;
            valid_.resize(n_, false);
            data_.resize(n_);
        }

        // 戻り値
        // - 存在するならtrue、存在しないならfalse
        // - index
        pair<bool, int> get_index(Key key) const
        {
            Key i = key % n_;
            while (valid_[i])
            {
                if (data_[i].first == key)
                {
                    return {true, i};
                }
                if (++i == n_)
                {
                    i = 0;
                }
            }
            return {false, i};
        }

        // 指定したindexにkeyとvalueを格納する
        void set(int i, Key key, T value)
        {
            valid_[i] = true;
            data_[i] = {key, value};
        }

        // 指定したindexのvalueを返す
        T get(int i) const
        {
            assert(valid_[i]);
            return data_[i].second;
        }

        void clear()
        {
            fill(valid_.begin(), valid_.end(), false);
        }

    private:
        uint32_t n_;
        vector<bool> valid_;
        vector<pair<Key, T>> data_;
    };

    using Hash = uint64_t;

    // 状態遷移を行うために必要な情報
    // メモリ使用量をできるだけ小さくしてください
    struct Action
    {
        int xyxy;

        Action(int a, int b, int c)
        {
            if(b == -1){
                xyxy = -(a+1);
            } else {
                xyxy = 400 * 400 * c + 400 * a + b;
            }
        }

        tuple<int, int, int> decode() const
        {
            if(xyxy < 0){
                return {-xyxy-1, -1, -1};
            } else {
                return {xyxy / 400 % 400, xyxy % 400, xyxy / (400 * 400)};
            }
        }

        bool operator==(const Action &other) const
        {
            return xyxy == other.xyxy;
        }
    };

    using Cost = int;

    // 状態のコストを評価するための構造体
    // メモリ使用量をできるだけ小さくしてください
    struct Evaluator
    {
        Cost score;

        Evaluator(Cost score) : score(score) {}

        // 低いほどよい
        Cost evaluate() const
        {
            return score;
        }
    };

    // 展開するノードの候補を表す構造体
    struct Candidate
    {
        Action action;
        Evaluator evaluator;
        Hash hash;
        int parent;

        Candidate(Action action, Evaluator evaluator, Hash hash, int parent) : action(action),
                                                                               evaluator(evaluator),
                                                                               hash(hash),
                                                                               parent(parent) {}
    };

    // ノードの候補から実際に追加するものを選ぶクラス
    // ビーム幅の個数だけ、評価がよいものを選ぶ
    // ハッシュ値が一致したものについては、評価がよいほうのみを残す
    class Selector
    {
    public:
        explicit Selector(const Config &config) : hash_to_index_(config.hash_map_capacity)
        {
            beam_width = config.beam_width;
            candidates_.reserve(beam_width);
            full_ = false;

            costs_.resize(beam_width);
            for (size_t i = 0; i < beam_width; ++i)
            {
                costs_[i] = {0, i};
            }
        }

        // 候補を追加する
        // ターン数最小化型の問題で、candidateによって実行可能解が得られる場合にのみ finished = true とする
        // ビーム幅分の候補をCandidateを追加したときにsegment treeを構築する
        void push(const Candidate &candidate, bool finished)
        {
            if (finished)
            {
                finished_candidates_.emplace_back(candidate);
                return;
            }
            Cost cost = candidate.evaluator.evaluate();
            if (full_ && cost >= st_.all_prod().first)
            {
                // 保持しているどの候補よりもコストが小さくないとき
                return;
            }
            auto [valid, i] = hash_to_index_.get_index(candidate.hash);

            if (valid)
            {
                int j = hash_to_index_.get(i);
                if (candidate.hash == candidates_[j].hash)
                {
                    // ハッシュ値が等しいものが存在しているとき
                    if (full_)
                    {
                        // segment treeが構築されている場合
                        if (cost < st_.get(j).first)
                        {
                            candidates_[j] = candidate;
                            st_.set(j, {cost, j});
                        }
                    }
                    else
                    {
                        // segment treeが構築されていない場合
                        if (cost < costs_[j].first)
                        {
                            candidates_[j] = candidate;
                            costs_[j].first = cost;
                        }
                    }
                    return;
                }
            }
            if (full_)
            {
                // segment treeが構築されている場合
                int j = st_.all_prod().second;
                hash_to_index_.set(i, candidate.hash, j);
                candidates_[j] = candidate;
                st_.set(j, {cost, j});
            }
            else
            {
                // segment treeが構築されていない場合
                int j = candidates_.size();
                hash_to_index_.set(i, candidate.hash, j);
                candidates_.emplace_back(candidate);
                costs_[j].first = cost;
                if (candidates_.size() == beam_width)
                {
                    // 保持している候補がビーム幅分になったときにsegment treeを構築する
                    full_ = true;
                    st_ = MaxSegtree(costs_);
                }
            }
        }

        // 選んだ候補を返す
        const vector<Candidate> &select() const
        {
            return candidates_;
        }

        // 実行可能解が見つかったか
        bool have_finished() const
        {
            return !finished_candidates_.empty();
        }

        // 実行可能解に到達するCandidateを返す
        vector<Candidate> get_finished_candidates() const
        {
            return finished_candidates_;
        }

        // 最もよいCandidateを返す
        Candidate calculate_best_candidate() const
        {
            if (full_)
            {
                size_t best = 0;
                for (size_t i = 0; i < beam_width; ++i)
                {
                    if (st_.get(i).first < st_.get(best).first)
                    {
                        best = i;
                    }
                }
                return candidates_[best];
            }
            else
            {
                size_t best = 0;
                for (size_t i = 0; i < candidates_.size(); ++i)
                {
                    if (costs_[i].first < costs_[best].first)
                    {
                        best = i;
                    }
                }
                return candidates_[best];
            }
        }

        void clear()
        {
            candidates_.clear();
            hash_to_index_.clear();
            full_ = false;
        }

    private:
        // 削除可能な優先度付きキュー
        using MaxSegtree = atcoder::segtree<
            pair<Cost, int>,
            [](pair<Cost, int> a, pair<Cost, int> b)
            {
                if (a.first >= b.first)
                {
                    return a;
                }
                else
                {
                    return b;
                }
            },
            []()
            { return make_pair(numeric_limits<Cost>::min(), -1); }>;

        size_t beam_width;
        vector<Candidate> candidates_;
        HashMap<Hash, int> hash_to_index_;
        bool full_;
        vector<pair<Cost, int>> costs_;
        MaxSegtree st_;
        vector<Candidate> finished_candidates_;
    };

    // 深さ優先探索に沿って更新する情報をまとめたクラス
    class State
    {
    public:
        explicit State(const Input &input) :
            x_(input.target[0].first), y_(input.target[0].second),
            seek_(0),
            target_(input.target),
            field_(input.N, 0),
            initial_hash_(20*input.target[0].first + input.target[0].second),
            isTarget_(input.N, vector<int>(input.N, 0))
        {
            for(auto& p : input.target){
                isTarget_[p.first][p.second] = 1;
            }
        }

        // EvaluatorとHashの初期値を返す
        pair<Evaluator, Hash> make_initial_node()
        {
            return {Evaluator(1000000), initial_hash_};
        }

        // 次の状態候補を全てselectorに追加する
        // 引数
        //   evaluator : 今の評価器
        //   hash      : 今のハッシュ値
        //   parent    : 今のノードID（次のノードにとって親となる）
        void expand(const Evaluator &evaluator, Hash hash, int parent, Selector &selector)
        {
            const int N = field_.size();
            auto warp = genWapp(N, field_);
            // move
            for(int d=0;d<4;d++){
                int nx = x_ + dx[d];
                int ny = y_ + dy[d];
                if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if(field_[nx] & (1 << ny)) continue;
                int nseek = seek_;
                if(nx == target_[seek_+1].first && ny == target_[seek_+1].second) ++nseek;
                Hash new_hash = (hash & (((1LL<<48)-1)<<16)) + (20*20+nseek + 20*nx + ny);
                int cost = minCost(new_hash, nx, ny, nseek, target_, field_, warp);
                if(20*nx+ny == 20*x_+y_) continue;
                selector.push(
                    Candidate(Action(20*x_+y_, 20*nx+ny, nseek - seek_),
                    Evaluator(cost),
                    new_hash,
                    parent),
                    nseek == target_.size()-1);
            }
            // slip
            for(int d=0;d<4;d++){
                int nx = d%2 == 0 ? warp[d][x_][y_] : x_;
                int ny = d%2 == 1 ? warp[d][x_][y_] : y_;
                if(field_[nx] & (1 << ny)) continue;
                int nseek = seek_;
                if(nx == target_[seek_+1].first && ny == target_[seek_+1].second) ++nseek;
                Hash new_hash = (hash & (((1LL<<48)-1)<<16)) + (20*20*nseek + 20*nx + ny);
                int cost = minCost(new_hash, nx, ny, nseek, target_, field_, warp);
                if(20*nx+ny == 20*x_+y_) continue;
                selector.push(
                    Candidate(Action(20*x_+y_, 20*nx+ny, nseek - seek_),
                    Evaluator(cost),
                    new_hash,
                    parent),
                    nseek == target_.size()-1);
            }
            // action
            for(int d=0;d<4;d++){
                int nx = x_ + dx[d];
                int ny = y_ + dy[d];
                if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if(isTarget_[nx][ny]) continue;
                field_[nx] ^= (1 << ny);
                Hash new_hash = hash ^= (Z[20*nx+ny] << 16);
                int cost = minCost(new_hash, x_, y_, seek_, target_, field_);
                field_[nx] ^= (1 << ny);
                selector.push(
                    Candidate(Action(d, -1, -1),
                    Evaluator(cost),
                    new_hash,
                    parent),
                    false);
            }
        }
        // actionを実行して次の状態に遷移する
        void move_forward(Action action)
        {
            auto [p1, p2, p3] = action.decode();
            if(p2 >= 0){
                x_ = p2 / 20;
                y_ = p2 % 20;
                seek_ += p3;
            } else {
                int x = x_ + dx[p1];
                int y = y_ + dy[p1];
                field_[x] ^= (1 << y);
            }
        }

        // actionを実行する前の状態に遷移する
        // 今の状態は、親からactionを実行して遷移した状態である
        void move_backward(Action action)
        {
            auto [p1, p2, p3] = action.decode();
            if(p2 >= 0){
                x_ = p1 / 20;
                y_ = p1 % 20;
                seek_ -= p3;
            } else {
                int x = x_ + dx[p1];
                int y = y_ + dy[p1];
                field_[x] ^= (1 << y);
            }
        }

    private:
        vector<pair<int, int>> target_;
        vector<int> field_;
        int x_;
        int y_;
        int seek_;
        Hash initial_hash_;
        vector<vector<int>> isTarget_;
    };

    // Euler Tourを管理するためのクラス
    class Tree
    {
    public:
        explicit Tree(const State &state, const Config &config) : state_(state)
        {
            curr_tour_.reserve(config.tour_capacity);
            next_tour_.reserve(config.tour_capacity);
            leaves_.reserve(config.beam_width);
            buckets_.assign(config.beam_width, {});
        }

        // 状態を更新しながら深さ優先探索を行い、次のノードの候補を全てselectorに追加する
        void dfs(Selector &selector)
        {
            if (curr_tour_.empty())
            {
                // 最初のターン
                auto [evaluator, hash] = state_.make_initial_node();
                state_.expand(evaluator, hash, 0, selector);
                return;
            }

            for (auto [leaf_index, action] : curr_tour_)
            {
                if (leaf_index >= 0)
                {
                    // 葉
                    state_.move_forward(action);
                    auto &[evaluator, hash] = leaves_[leaf_index];
                    state_.expand(evaluator, hash, leaf_index, selector);
                    state_.move_backward(action);
                }
                else if (leaf_index == -1)
                {
                    // 前進辺
                    state_.move_forward(action);
                }
                else
                {
                    // 後退辺
                    state_.move_backward(action);
                }
            }
        }

        // 木を更新する
        void update(const vector<Candidate> &candidates)
        {
            leaves_.clear();

            if (curr_tour_.empty())
            {
                // 最初のターン
                for (const Candidate &candidate : candidates)
                {
                    curr_tour_.push_back({(int)leaves_.size(), candidate.action});
                    leaves_.push_back({candidate.evaluator, candidate.hash});
                }
                return;
            }

            for (const Candidate &candidate : candidates)
            {
                buckets_[candidate.parent].push_back({candidate.action, candidate.evaluator, candidate.hash});
            }

            auto it = curr_tour_.begin();

            // 一本道を反復しないようにする
            while (it->first == -1 && it->second == curr_tour_.back().second)
            {
                Action action = (it++)->second;
                state_.move_forward(action);
                direct_road_.push_back(action);
                curr_tour_.pop_back();
            }

            // 葉の追加や不要な辺の削除をする
            while (it != curr_tour_.end())
            {
                auto [leaf_index, action] = *(it++);
                if (leaf_index >= 0)
                {
                    // 葉
                    if (buckets_[leaf_index].empty())
                    {
                        continue;
                    }
                    next_tour_.push_back({-1, action});
                    for (auto [new_action, evaluator, hash] : buckets_[leaf_index])
                    {
                        int new_leaf_index = leaves_.size();
                        next_tour_.push_back({new_leaf_index, new_action});
                        leaves_.push_back({evaluator, hash});
                    }
                    buckets_[leaf_index].clear();
                    next_tour_.push_back({-2, action});
                }
                else if (leaf_index == -1)
                {
                    // 前進辺
                    next_tour_.push_back({-1, action});
                }
                else
                {
                    // 後退辺
                    auto [old_leaf_index, old_action] = next_tour_.back();
                    if (old_leaf_index == -1)
                    {
                        next_tour_.pop_back();
                    }
                    else
                    {
                        next_tour_.push_back({-2, action});
                    }
                }
            }
            swap(curr_tour_, next_tour_);
            next_tour_.clear();
        }

        // 根からのパスを取得する
        vector<Action> calculate_path(int parent, int turn) const
        {

            vector<Action> ret = direct_road_;
            ret.reserve(turn);
            for (auto [leaf_index, action] : curr_tour_)
            {
                if (leaf_index >= 0)
                {
                    if (leaf_index == parent)
                    {
                        ret.push_back(action);
                        return ret;
                    }
                }
                else if (leaf_index == -1)
                {
                    ret.push_back(action);
                }
                else
                {
                    ret.pop_back();
                }
            }
        }

    private:
        State state_;
        vector<pair<int, Action>> curr_tour_;
        vector<pair<int, Action>> next_tour_;
        vector<pair<Evaluator, Hash>> leaves_;
        vector<vector<tuple<Action, Evaluator, Hash>>> buckets_;
        vector<Action> direct_road_;
    };

    // ビームサーチを行う関数
    vector<Action> beam_search(const Config &config, const State &state, const Timer &timer)
    {
        Tree tree(state, config);

        // 新しいノード候補の集合
        Selector selector(config);

        for (int turn = 0; turn < config.max_turn; ++turn)
        {
            // cerr << "turn" << turn << endl;
            // Euler Tourでselectorに候補を追加する
            debug = true;
            tree.dfs(selector);

            if (selector.have_finished())
            {
                // ターン数最小化型の問題で実行可能解が見つかったとき
                Candidate candidate = selector.get_finished_candidates()[0];
                vector<Action> ret = tree.calculate_path(candidate.parent, turn + 1);
                ret.push_back(candidate.action);
                return ret;
            }

            assert(!selector.select().empty());

            {
                Candidate best_candidate = selector.calculate_best_candidate();
                // cerr << "turn: " << turn << " score: " << best_candidate.evaluator.score << endl;
            }

            if (turn == config.max_turn - 1)
            {
                cerr << "end" << endl;
                // ターン数固定型の問題で全ターンが終了したとき
                Candidate best_candidate = selector.calculate_best_candidate();
                cerr << "best_candidate: " << best_candidate.evaluator.score << endl;
                vector<Action> ret = tree.calculate_path(best_candidate.parent, turn + 1);
                cerr << "ret: " << ret.size() << endl;
                ret.push_back(best_candidate.action);
                cerr << "ret: " << ret.size() << endl;
                return ret;
            }

            // 木を更新する
            tree.update(selector.select());

            selector.clear();
        }
    }

} // namespace beam_search

struct Solver
{
    const Input input;
    vector<beam_search::Action> output;

    Solver(const Input &input) : input(input) {}

    void solve(const Timer &timer)
    {
        size_t beam_width = 10;
        size_t tour_capacity = 30 * beam_width;
        uint32_t hash_map_capacity = 32 * 3 * beam_width;
        beam_search::Config config = {
            2*20*40,
            beam_width,
            tour_capacity,
            hash_map_capacity};
        beam_search::State state(input);
        output = beam_search::beam_search(config, state, timer);
    }

    void print() const
    {
        vector<tuple<int, int, int, int>> ret;
        for (auto &action : output)
        {
            auto [p1, p2, p3] = action.decode();
            if(p2 >= 0){
                int x1 = p1/20;
                int y1 = p1%20;
                int x2 = p2/20;
                int y2 = p2%20;
                if(x1 == x2){
                    if(y1+1 == y2){
                        cout << "M R" << endl;
                    } else if(y1-1 == y2){
                        cout << "M L" << endl;
                    } else if(y1 < y2){
                        cout << "S R" << endl;
                    } else if(y1 > y2){
                        cout << "S L" << endl;
                    }
                } else {
                    if(x1+1 == x2){
                        cout << "M D" << endl;
                    } else if(x1-1 == x2){
                        cout << "M U" << endl;
                    } else if(x1 < x2){
                        cout << "S D" << endl;
                    } else if(x1 > x2){
                        cout << "S U" << endl;
                    }
                }
            } else {
                cout << "A " << "DRUL"[p1] << endl;
            }
        }
    }
};

int main()
{
    Timer timer;
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Input input;
    input.input();

    Solver solver(input);
    solver.solve(timer);
    solver.print();

    cerr << call << " " << cnt << endl;

    return 0;
}