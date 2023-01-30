#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <thread>
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

XorShift globalRandom(123456789UL);

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
}

//------------------------------------------------------------------------------
struct Node {
    explicit Node(int p=0, int w=0, int idx=0) : pos(p), weight(w), idx(idx){}
    int pos, weight, idx;
};

struct Edge {
    explicit Edge(int src=0, int dst=0, int w=0) : src(src), dst(dst), weight(w){}
    int src, dst, weight;
};

//------------------------------------------------------------------------------
vector<int> dijkstra(const vector<vector<Node>>& g, int src){
    auto compNode = [](const Node& a, const Node& b){
        return a.weight > b.weight;
    };
    priority_queue<Node, vector<Node>, decltype(compNode)> qu(compNode);
    vector<int> res(g.size(), 1000000000);
    res[src] = 0;
    qu.emplace(src, 0);
    while(!qu.empty()){
        int curPos = qu.top().pos;
        int curCost = qu.top().weight;
        qu.pop();
        if(res[curPos] != curCost) continue;
        for(auto& nxt : g[curPos]){
            const int nextPos = nxt.pos;
            const int nextCost = curCost + nxt.weight;
            if(nextCost < res[nextPos]){
                res[nextPos] = nextCost;
                qu.emplace(nextPos, nextCost);
            }
        }
    }
    return res;
}

//------------------------------------------------------------------------------
vector<int> distanceBFS(const vector<vector<Node>>& g, int src){
    queue<int> qu;
    const int INF = 1000000000;
    vector<int> res(g.size(), INF);
    res[src] = 0;
    qu.emplace(src);
    while(!qu.empty()){
        int curPos = qu.front(); qu.pop();
        for(auto& nxt : g[curPos]){
            const int nextPos = nxt.pos;
            if(res[nextPos] != INF) continue;
            if(nxt.weight == INF) continue;
            res[nextPos] = res[curPos] + 1;
            qu.emplace(nextPos);
        }
    }
    return res;
}

//------------------------------------------------------------------------------
void dijkstra(const vector<vector<Node>>& g, vector<int>& res, int src){
    priority_queue<pair<int, int>> qu;
    for(int i=0;i<=src;i++) qu.emplace(-res[i], i);
    while(!qu.empty()){
        int curPos = qu.top().second;
        int curCost = -qu.top().first;
        qu.pop();
        if(res[curPos] != curCost) continue;
        for(auto& nxt : g[curPos]){
            const int nextPos = nxt.pos;
            const int nextCost = curCost + nxt.weight;
            if(nextCost < res[nextPos]){
                res[nextPos] = nextCost;
                qu.emplace(-nextCost, nextPos);
            }
        }
    }
}

//------------------------------------------------------------------------------
vector<vector<int>> allDistance(const vector<vector<Node>>& g){
    vector<vector<int>> res;
    for(int i=0;i<g.size();i++) res.emplace_back(dijkstra(g, i));
    return res;
}

//------------------------------------------------------------------------------
vector<vector<int>> allDistanceBFS(const vector<vector<Node>>& g){
    vector<vector<int>> res;
    for(int i=0;i<g.size();i++) res.emplace_back(distanceBFS(g, i));
    return res;
}

//------------------------------------------------------------------------------
long long calcPenalty(vector<vector<Node>>& g,
                      const vector<Edge>& edges,
                      const vector<pair<int,int>>& edgeIdx,
                      const vector<vector<int>>& baseCost,
                      const vector<int>& removes)
{
    long long penalty = 0;
    vector<int> curW;
    curW.reserve(removes.size());
    for(int idx : removes){
        curW.push_back(g[edges[idx].src][edgeIdx[idx].first].weight);
        g[edges[idx].src][edgeIdx[idx].first].weight = 1000000000;
        g[edges[idx].dst][edgeIdx[idx].second].weight = 1000000000;
    }
    for(int i=0;i+1<g.size();i++){
        auto dif = dijkstra(g, i);
        for(int j=i+1;j<g.size();j++) penalty += 2 * (dif[j] - baseCost[i][j]);
    }
    for(int i=0;i<removes.size();i++){
        const int idx = removes[i];
        const int w = curW[i];
        g[edges[idx].src][edgeIdx[idx].first].weight = w;
        g[edges[idx].dst][edgeIdx[idx].second].weight = w;
    }
    return penalty;
}

//------------------------------------------------------------------------------
long long calcPenaltyBFS(vector<vector<Node>>& g,
                      const vector<Edge>& edges,
                      const vector<pair<int,int>>& edgeIdx,
                      const vector<vector<int>>& baseCost,
                      const vector<vector<int>>& groups,
                      const vector<int>& removeGroups)
{
    long long penalty = 0;
    for(const auto& groupIdx : removeGroups){
        for(int idx : groups[groupIdx]){
            g[edges[idx].src][edgeIdx[idx].first].weight = 1000000000;
            g[edges[idx].dst][edgeIdx[idx].second].weight = 1000000000;
        }
    }
    for(int i=0;i+1<g.size();i++){
        auto dif = distanceBFS(g, i);
        for(int j=i+1;j<g.size();j++) penalty += 2 * (dif[j] - baseCost[i][j]);
    }
    for(const auto& groupIdx : removeGroups){
        for(int idx : groups[groupIdx]){
            g[edges[idx].src][edgeIdx[idx].first].weight = edges[idx].weight;
            g[edges[idx].dst][edgeIdx[idx].second].weight = edges[idx].weight;
        }
    }
    return penalty;
}

//------------------------------------------------------------------------------
long long calcPenalty(vector<vector<Node>>& g,
                      const vector<Edge>& edges,
                      const vector<pair<int,int>>& edgeIdx,
                      const vector<vector<int>>& baseCost,
                      const vector<vector<int>>& groups,
                      const vector<int>& removeGroups)
{
    long long penalty = 0;
    for(const auto& groupIdx : removeGroups){
        for(int idx : groups[groupIdx]){
            g[edges[idx].src][edgeIdx[idx].first].weight = 1000000000;
            g[edges[idx].dst][edgeIdx[idx].second].weight = 1000000000;
        }
    }
    for(int i=0;i+1<g.size();i++){
        auto dif = dijkstra(g, i);
        for(int j=i+1;j<g.size();j++) penalty += 2 * (dif[j] - baseCost[i][j]);
    }
    for(const auto& groupIdx : removeGroups){
        for(int idx : groups[groupIdx]){
            g[edges[idx].src][edgeIdx[idx].first].weight = edges[idx].weight;
            g[edges[idx].dst][edgeIdx[idx].second].weight = edges[idx].weight;
        }
    }
    return penalty;
}

//------------------------------------------------------------------------------
long long calcScore(vector<vector<Node>>& g,
                    const vector<Edge>& edges,
                    const vector<pair<int,int>>& edgeIdx,
                    const vector<vector<int>>& baseCost,
                    const vector<vector<int>>& res)
{
    long long score = 0;
    for(auto& r : res){
        auto penalty = calcPenalty(g, edges, edgeIdx, baseCost, r);
        score += penalty;
    }
    return (10000 * score / (g.size() * (g.size()-1) * res.size()) + 5) / 10;
}

//------------------------------------------------------------------------------
vector<vector<int>> generateRandomSolution(const vector<Edge>& edges, const Timer& timer, int N, int M, int D, int K){
    vector<int> order(M);
    vector<vector<int>> res;
    vector<vector<int>> removeList(D, vector<int>(M, 0));
    int base = 0;
    for(int i=0;i<D;i++){
        res.emplace_back((M+i)/D);
        int end = base + (M+i)/D;
        for(int j=base;j<end;j++) order[j] = i;
        base = end;
    }
    shuffle(order.begin(), order.end(), globalRandom);
    vector<int> idx(D, 0);
    for(int i=0;i<M;i++){
        res[order[i]][idx[order[i]]++] = i;
    }
    for(int i=0;i<D;i++){
        for(auto& t : res[i]) removeList[i][t] = 1;
    }
    auto calcScore = [&](const vector<int>& removed){
        UnionFind uf(N);
        int t = 0;
        int rest = N-1;
        for(int j=0;j<M;j++){
            if(removed[j]) continue;
            const int p = uf.getRoot(edges[j].src);
            const int q = uf.getRoot(edges[j].dst);
            if(p != q){
                uf.merge(p, q);
                --rest;
                if(!rest) return 0;
            }
        }
        return rest;
    };
    int scoreSum = 0;
    vector<int> scores(D);
    for(int i=0;i<D;i++){
        scores[i] = calcScore(removeList[i]);
        scoreSum += scores[i];
    }
    vector<int> separates(D);
    int trynum = 0;
    while(timer.msec() < 5000 && scoreSum > 0){
        ++trynum;
        int sepNum = 0;
        for(int i=0;i<D;i++) if(scores[i]) separates[sepNum++] = i;
        int p = separates[globalRandom()%sepNum];
        int q = globalRandom()%D;
        while(p == q || res[q].empty()) q = globalRandom()%D;
        // if(true){
        if(globalRandom()%8 || res[q].size() == K){
            // swap
            const int pIdx = globalRandom()%res[p].size();
            const int qIdx = globalRandom()%res[q].size();
            removeList[p][res[p][pIdx]] = 0;
            removeList[p][res[q][qIdx]] = 1;
            removeList[q][res[p][pIdx]] = 1;
            removeList[q][res[q][qIdx]] = 0;
            swap(res[p][pIdx], res[q][qIdx]);
            int np = calcScore(removeList[p]);
            int nq = calcScore(removeList[q]);
            if(np+nq > scores[p]+scores[q]){
                swap(res[p][pIdx], res[q][qIdx]);
                removeList[p][res[p][pIdx]] = 1;
                removeList[p][res[q][qIdx]] = 0;
                removeList[q][res[p][pIdx]] = 0;
                removeList[q][res[q][qIdx]] = 1;
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
            }
        } else {
            // move
            const int pIdx = globalRandom()%res[p].size();
            if(pIdx+1 != res[p].size()) swap(res[p][pIdx], res[p].back());
            removeList[p][res[p].back()] = 0;
            removeList[q][res[p].back()] = 1;
            res[q].push_back(res[p].back());
            res[p].pop_back();
            int np = calcScore(removeList[p]);
            int nq = calcScore(removeList[q]);
            if(np+nq > scores[p]+scores[q]){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                removeList[p][res[p].back()] = 1;
                removeList[q][res[p].back()] = 0;
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
            }
        }
        // validatoin
        vector<int> seen(M, 0);
        for(auto& v : res){
            for(auto& t : v) seen[t] = 1;
        }
        for(int j=0;j<M;j++) if(!seen[j]) cerr << "Edge " << j << " disappeared!" << endl;
        int newScore = 0;
        for(int j=0;j<D;j++){
            int nc = calcScore(removeList[j]);
            if(nc != scores[j]) cerr << "Score " << j << " is wrong, expected: " << nc << ", actual: " << scores[j] << endl;
        }
    }
    cerr << "trynum: " << trynum << endl;
    return res;
}

//------------------------------------------------------------------------------
void printSolution(const vector<vector<int>>& assign, int M){
    vector<int> res(M, -1);
    for(int i=0;i<assign.size();i++){
        for(int t : assign[i]) res[t] = i+1;
    }
    for(int t : res) cout << t << " ";
    cout << endl;
}

//------------------------------------------------------------------------------
vector<vector<int>> improveSolution(vector<vector<Node>>& g,
                                    const vector<Edge>& edges,
                                    const vector<pair<int,int>>& edgeIdx,
                                    const vector<vector<int>>& baseCost,
                                    const vector<vector<int>>& removeEdges,
                                    int K)
{
    Timer timer;
    auto res = removeEdges;
    const int D = res.size();
    const int N = g.size();
    const int M = edges.size();
    auto calcScore = [&](const vector<int>& removed){
        UnionFind uf(N);
        int t = 0;
        int rest = N-1;
        for(int j=0;j<M;j++){
            if(removed[j]) continue;
            const int p = uf.getRoot(edges[j].src);
            const int q = uf.getRoot(edges[j].dst);
            if(p != q){
                uf.merge(p, q);
                --rest;
                if(!rest) return 0;
            }
        }
        return rest;
    };
    vector<vector<int>> removeList(D, vector<int>(M, 0));
    for(int i=0;i<D;i++){
        for(auto& t : res[i]) removeList[i][t] = 1;
    }
    vector<long long> scores(D);
    for(int i=0;i<D;i++) scores[i] = calcPenalty(g, edges, edgeIdx, baseCost, removeEdges[i]);
    long long scoreSum = accumulate(scores.begin(), scores.end(), 0LL);
    auto showScore = [&](int tryNum){
        // cerr << "tryNum: " << tryNum << " (time: " << timer.msec() << ")" << endl;
        // cerr << "score: " << (10000 * scoreSum / (g.size() * (g.size()-1) * res.size()) + 5) / 10 << endl;
        // vector<int> a(M, -1);
        // for(int i=0;i<res.size();i++){
        //     for(int t : res[i]) a[t] = i+1;
        // }
        // for(int t : a) cerr << t << " ";
        // cerr << endl;
    };
    for(int tryNum=1;tryNum<=10000000;tryNum++){
        if(timer.msec() > 5000){
            cerr << "trynum: " << tryNum << endl;
            break;
        }
        int sepNum = 0;
        int p = globalRandom()%D;
        int q = globalRandom()%D;
        while(p == q || res[p].empty()) q = globalRandom()%D;
        if(!res[q].empty() && (globalRandom()%8 || res[q].size() == K)){
            // swap
            const int pIdx = globalRandom()%res[p].size();
            const int qIdx = globalRandom()%res[q].size();
            removeList[p][res[p][pIdx]] = 0;
            removeList[p][res[q][qIdx]] = 1;
            removeList[q][res[p][pIdx]] = 1;
            removeList[q][res[q][qIdx]] = 0;
            swap(res[p][pIdx], res[q][qIdx]);
            if(calcScore(removeList[p]) > 0 || calcScore(removeList[q]) > 0){
                swap(res[p][pIdx], res[q][qIdx]);
                removeList[p][res[p][pIdx]] = 1;
                removeList[p][res[q][qIdx]] = 0;
                removeList[q][res[p][pIdx]] = 0;
                removeList[q][res[q][qIdx]] = 1;
                continue;
            }
            long long np = calcPenalty(g, edges, edgeIdx, baseCost, res[p]);
            long long nq = calcPenalty(g, edges, edgeIdx, baseCost, res[q]);
            if(np + nq < scores[p] + scores[q]){
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
                showScore(tryNum);
            } else {
                swap(res[p][pIdx], res[q][qIdx]);
                removeList[p][res[p][pIdx]] = 1;
                removeList[p][res[q][qIdx]] = 0;
                removeList[q][res[p][pIdx]] = 0;
                removeList[q][res[q][qIdx]] = 1;
            }
        } else {
            // move
            const int pIdx = globalRandom()%res[p].size();
            if(pIdx+1 != res[p].size()) swap(res[p][pIdx], res[p].back());
            removeList[p][res[p].back()] = 0;
            removeList[q][res[p].back()] = 1;
            res[q].push_back(res[p].back());
            res[p].pop_back();
            if(calcScore(removeList[p]) > 0 || calcScore(removeList[q]) > 0){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                removeList[p][res[p].back()] = 1;
                removeList[q][res[p].back()] = 0;
                continue;
            }
            long long np = calcPenalty(g, edges, edgeIdx, baseCost, res[p]);
            long long nq = calcPenalty(g, edges, edgeIdx, baseCost, res[q]);
            if(np+nq >= scores[p]+scores[q]){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                removeList[p][res[p].back()] = 1;
                removeList[q][res[p].back()] = 0;
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
                showScore(tryNum);
            }
        }
    }
    return res;
}

//------------------------------------------------------------------------------
vector<vector<int>> improveSolution(vector<vector<Node>>& g,
                                    const vector<Edge>& edges,
                                    const vector<pair<int,int>>& edgeIdx,
                                    const vector<Edge>& dual,
                                    const vector<vector<int>>& baseCost,
                                    const vector<vector<int>>& groups,
                                    const vector<vector<int>>& removeGroups,
                                    const Timer timer,
                                    int K,
                                    int dualSize)
{
    auto res = removeGroups;
    const int D = res.size();
    const int N = g.size();
    const int M = edges.size();
    auto connected = [&](const vector<int>& groupList){
        UnionFind uf(dualSize);
        int res = 0;
        for(const auto& groupIdx : groupList){
            for(const auto& t : groups[groupIdx]){
                const int p = uf.getRoot(dual[t].src);
                const int q = uf.getRoot(dual[t].dst);
                if(p == q) return false;
                else uf.merge(p, q);
            }
        }
        return true;
    };

    auto printScore = [&](long long baseScore, const vector<int>& list){
        // double n = g.size();
        // printf("%.8lf\n", baseScore/(n * (n - 1.0)));
        // cout << list.size();
        // for(auto& t : list) cout << " " << t;
        // cout << endl;
    };

    vector<long long> scores(D);
    for(int i=0;i<D;i++){
        scores[i] = calcPenalty(g, edges, edgeIdx, baseCost, groups, res[i]);
        printScore(scores[i], res[i]);
    }
    long long scoreSum = accumulate(scores.begin(), scores.end(), 0LL);
    vector<int> resSize(D, 0);
    for(int i=0;i<D;i++){
        for(auto& t : res[i]) resSize[i] += groups[t].size();
    }
    auto showScore = [&](int tryNum){
        cerr << "tryNum: " << tryNum << " (time: " << timer.msec() << ")" << endl;
        cerr << "score: " << (10000 * scoreSum / (g.size() * (g.size()-1) * res.size()) + 5) / 10 << endl;
        // vector<int> a(M, -1);
        // for(int i=0;i<res.size();i++){
        //     for(int t : res[i]) a[t] = i+1;
        // }
        // for(int t : a) cerr << t << " ";
        // cerr << endl;
    };
    for(int tryNum=1;tryNum<=10000000;tryNum++){
        if(timer.msec() > 8 * 60 * 60000){
            cerr << "trynum: " << tryNum << endl;
            break;
        }
        int sepNum = 0;
        int p = globalRandom()%D;
        int q = globalRandom()%D;
        while(p == q || res[p].empty()){
            if(res[p].empty()) p = globalRandom()%D;
            else q = globalRandom()%D;
        }
        if(!res[q].empty() && globalRandom()%8){
            // swap
            const int pIdx = globalRandom()%res[p].size();
            const int qIdx = globalRandom()%res[q].size();
            const auto& pGroup = groups[res[p][pIdx]];
            const auto& qGroup = groups[res[q][qIdx]];
            resSize[p] -= pGroup.size();
            resSize[p] += qGroup.size();
            resSize[q] -= qGroup.size();
            resSize[q] += pGroup.size();
            swap(res[p][pIdx], res[q][qIdx]);
            if(resSize[p] > K || resSize[q] > K || !connected(res[p]) || !connected(res[q])){
                swap(res[p][pIdx], res[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
                continue;
            }
            long long np = calcPenalty(g, edges, edgeIdx, baseCost, groups, res[p]);
            long long nq = calcPenalty(g, edges, edgeIdx, baseCost, groups, res[q]);
            printScore(np, res[p]);
            printScore(nq, res[q]);
            if(np + nq < scores[p] + scores[q]){
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
                showScore(tryNum);
            } else {
                swap(res[p][pIdx], res[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
            }
        } else {
            // move
            const int pIdx = globalRandom()%res[p].size();
            if(pIdx+1 != res[p].size()) swap(res[p][pIdx], res[p].back());
            const auto& pGroup = groups[res[p].back()];
            resSize[p] -= pGroup.size();
            resSize[q] += pGroup.size();
            res[q].push_back(res[p].back());
            res[p].pop_back();
            if(resSize[p] > K || resSize[q] > K || !connected(res[p]) || !connected(res[q])){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                resSize[p] += pGroup.size();
                resSize[q] -= pGroup.size();
                continue;
            }
            long long np = calcPenalty(g, edges, edgeIdx, baseCost, groups, res[p]);
            long long nq = calcPenalty(g, edges, edgeIdx, baseCost, groups, res[q]);
            printScore(np, res[p]);
            printScore(nq, res[q]);
            if(np+nq >= scores[p]+scores[q]){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                resSize[p] += pGroup.size();
                resSize[q] -= pGroup.size();
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
                showScore(tryNum);
            }
        }
    }
    return res;
}

//------------------------------------------------------------------------------
vector<vector<int>> improveSolutionBFS(vector<vector<Node>>& g,
                                    const vector<Edge>& edges,
                                    const vector<pair<int,int>>& edgeIdx,
                                    const vector<Edge>& dual,
                                    const vector<vector<int>>& groups,
                                    const vector<vector<int>>& removeGroups,
                                    const Timer timer,
                                    int K,
                                    int dualSize)
{
    const auto baseCost = allDistanceBFS(g);
    auto res = removeGroups;
    const int D = res.size();
    const int N = g.size();
    const int M = edges.size();
    auto connected = [&](const vector<int>& groupList){
        UnionFind uf(dualSize);
        int res = 0;
        for(const auto& groupIdx : groupList){
            for(const auto& t : groups[groupIdx]){
                const int p = uf.getRoot(dual[t].src);
                const int q = uf.getRoot(dual[t].dst);
                if(p == q) return false;
                else uf.merge(p, q);
            }
        }
        return true;
    };

    auto printScore = [&](long long baseScore, const vector<int>& list){
        // double n = g.size();
        // printf("%.8lf\n", baseScore/(n * (n - 1.0)));
        // cout << list.size();
        // for(auto& t : list) cout << " " << t;
        // cout << endl;
    };

    vector<long long> scores(D);
    for(int i=0;i<D;i++){
        scores[i] = calcPenaltyBFS(g, edges, edgeIdx, baseCost, groups, res[i]);
        printScore(scores[i], res[i]);
    }
    long long scoreSum = accumulate(scores.begin(), scores.end(), 0LL);
    vector<int> resSize(D, 0);
    for(int i=0;i<D;i++){
        for(auto& t : res[i]) resSize[i] += groups[t].size();
    }
    auto showScore = [&](int tryNum){
        cerr << "tryNum: " << tryNum << " (time: " << timer.msec() << ")" << endl;
        cerr << "score: " << (10000 * scoreSum / (g.size() * (g.size()-1) * res.size()) + 5) / 10 << endl;
        // vector<int> a(M, -1);
        // for(int i=0;i<res.size();i++){
        //     for(int t : res[i]) a[t] = i+1;
        // }
        // for(int t : a) cerr << t << " ";
        // cerr << endl;
    };
    for(int tryNum=1;tryNum<=10000000;tryNum++){
        if(timer.msec() > 5500){
            cerr << "trynum: " << tryNum << endl;
            break;
        }
        int sepNum = 0;
        int p = globalRandom()%D;
        int q = globalRandom()%D;
        while(p == q || res[p].empty()){
            if(res[p].empty()) p = globalRandom()%D;
            else q = globalRandom()%D;
        }
        if(!res[q].empty() && globalRandom()%8){
            // swap
            const int pIdx = globalRandom()%res[p].size();
            const int qIdx = globalRandom()%res[q].size();
            const auto& pGroup = groups[res[p][pIdx]];
            const auto& qGroup = groups[res[q][qIdx]];
            resSize[p] -= pGroup.size();
            resSize[p] += qGroup.size();
            resSize[q] -= qGroup.size();
            resSize[q] += pGroup.size();
            swap(res[p][pIdx], res[q][qIdx]);
            if(resSize[p] > K || resSize[q] > K || !connected(res[p]) || !connected(res[q])){
                swap(res[p][pIdx], res[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
                continue;
            }
            long long np = calcPenaltyBFS(g, edges, edgeIdx, baseCost, groups, res[p]);
            long long nq = calcPenaltyBFS(g, edges, edgeIdx, baseCost, groups, res[q]);
            printScore(np, res[p]);
            printScore(nq, res[q]);
            if(np + nq < scores[p] + scores[q]){
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
                showScore(tryNum);
            } else {
                swap(res[p][pIdx], res[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
            }
        } else {
            // move
            const int pIdx = globalRandom()%res[p].size();
            if(pIdx+1 != res[p].size()) swap(res[p][pIdx], res[p].back());
            const auto& pGroup = groups[res[p].back()];
            resSize[p] -= pGroup.size();
            resSize[q] += pGroup.size();
            res[q].push_back(res[p].back());
            res[p].pop_back();
            if(resSize[p] > K || resSize[q] > K || !connected(res[p]) || !connected(res[q])){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                resSize[p] += pGroup.size();
                resSize[q] -= pGroup.size();
                continue;
            }
            long long np = calcPenaltyBFS(g, edges, edgeIdx, baseCost, groups, res[p]);
            long long nq = calcPenaltyBFS(g, edges, edgeIdx, baseCost, groups, res[q]);
            printScore(np, res[p]);
            printScore(nq, res[q]);
            if(np+nq >= scores[p]+scores[q]){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                resSize[p] += pGroup.size();
                resSize[q] -= pGroup.size();
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
                showScore(tryNum);
            }
        }
    }
    return res;
}

//------------------------------------------------------------------------------
vector<vector<int>> improveSolutionBFS2(const vector<vector<Node>>& g,
                                    const vector<Edge>& edges,
                                    const vector<pair<int,int>>& coord,
                                    const vector<pair<int,int>>& edgeIdx,
                                    const vector<Edge>& dual,
                                    const vector<vector<int>>& groups,
                                    const vector<vector<int>>& removeGroups,
                                    const Timer timer,
                                    int K,
                                    int dualSize)
{
    const auto baseCost = allDistanceBFS(g);
    auto res = removeGroups;
    const int D = res.size();
    const int N = g.size();
    const int M = edges.size();
    auto connected = [&](const vector<int>& groupList){
        UnionFind uf(dualSize);
        int res = 0;
        for(const auto& groupIdx : groupList){
            for(const auto& t : groups[groupIdx]){
                const int p = uf.getRoot(dual[t].src);
                const int q = uf.getRoot(dual[t].dst);
                if(p == q) return false;
                else uf.merge(p, q);
            }
        }
        return true;
    };

    vector<vector<double>> params(groups.size(), vector<double>(groups.size()));
    {
        vector<std::pair<double, double>> dir(groups.size());
        vector<std::pair<int, int>> groupEdge(groups.size());
        vector<double> groupLength(groups.size());

        for(int i=0;i<groups.size();i++){
            if(groups[i].size() == 1){
                groupEdge[i].first = edges[groups[i].front()].src;
                groupEdge[i].second = edges[groups[i].front()].dst;
            } else {
                groupEdge[i].first = edges[groups[i].front()].src;
                groupEdge[i].second = edges[groups[i].back()].dst;
                if(groupEdge[i].first == edges[groups[i][1]].src || groupEdge[i].first == edges[groups[i][1]].dst){
                    groupEdge[i].first = edges[groups[i].front()].dst;
                }
                if(groupEdge[i].second == edges[groups[i][groups[i].size()-2]].src || groupEdge[i].second == edges[groups[i][groups[i].size()-2]].dst){
                    groupEdge[i].second = edges[groups[i].back()].src;
                }
            }
        }

        for(int i=0;i<groups.size();i++){
            double dx = coord[groupEdge[i].second].first - coord[groupEdge[i].first].first;
            double dy = coord[groupEdge[i].second].second - coord[groupEdge[i].first].second;
            double len = sqrt(dx*dx+dy*dy);
            groupLength[i] = len;
            dir[i].first = dx/len;
            dir[i].second = dy/len;
        }

        for(int i=0;i<groups.size();i++){
            for(int j=0;j<groups.size();j++){
                if(i == j) continue;
                if(groupLength[i] < groupLength[j]) continue;
                if(groupLength[i] == groupLength[j] && i > j) continue;
                const auto& gi = groups[i];
                const auto& gj = groups[j];
                int dist = 1000000000;
                for(int ii : gi){
                    for(int jj : gj){
                        dist = min(dist, baseCost[edges[ii].src][edges[jj].src]);
                        dist = min(dist, baseCost[edges[ii].src][edges[jj].dst]);
                        dist = min(dist, baseCost[edges[ii].dst][edges[jj].src]);
                        dist = min(dist, baseCost[edges[ii].dst][edges[jj].dst]);
                    }
                }
                double pa, pb;
                const auto& src = coord[groupEdge[i].first];
                const auto& dst1 = coord[groupEdge[j].first];
                const auto& dst2 = coord[groupEdge[j].second];
                {
                    double dx = dst1.first - src.first;
                    double dy = dst1.second - src.second;
                    pa = dx * dir[i].first + dy * dir[i].second;
                }
                {
                    double dx = dst2.first - src.first;
                    double dy = dst2.second - src.second;
                    pb = dx * dir[i].first + dy * dir[i].second;
                }
                if(pa > pb) swap(pa, pb);
                double overlap = max(0.0, min(groupLength[i], pb) - max(0.0, pa));
                double outer = max(0.0, pb - max(groupLength[i], pa)) + max(0.0, min(0.0, pb) - pa);
                params[i][j] = params[j][i] = (4 * overlap - outer)/((dist+1)*(dist+1));
            }
        }
    }

    double scoreSum = 0.0;
    for(int i=0;i<D;i++){
        for(int j=0;j<res[i].size();j++){
            for(int k=j+1;k<res[i].size();k++) scoreSum += params[res[i][j]][res[i][k]];
        }
    }
    cerr << scoreSum << endl;
    vector<int> resSize(D, 0);
    for(int i=0;i<D;i++){
        for(auto& t : res[i]) resSize[i] += groups[t].size();
    }
    auto showScore = [&](int tryNum){
        cerr << "tryNum: " << tryNum << " (time: " << timer.msec() << ")" << endl;
        cerr << scoreSum << endl;
    };
    const double first_time = timer.msec();
    const double time_limit = 5800;
    const double initial_temp = 10.0;
    const double final_temp = 0.01;
    for(int tryNum=1;tryNum<=10000000;tryNum++){
        if(timer.msec() > time_limit){
            cerr << "trynum: " << tryNum << endl;
            break;
        }

        const double ratio = (timer.msec() - first_time) / (time_limit - first_time);
        const double rev_ratio = 1 - ratio;
        const double temperature = initial_temp + (final_temp - initial_temp) * (1 - rev_ratio * rev_ratio * rev_ratio);

        int sepNum = 0;
        int p = globalRandom()%D;
        int q = globalRandom()%D;
        while(p == q || res[p].empty()){
            if(res[p].empty()) p = globalRandom()%D;
            else q = globalRandom()%D;
        }
        if(!res[q].empty() && globalRandom()%8){
            // swap
            const int pIdx = globalRandom()%res[p].size();
            const int qIdx = globalRandom()%res[q].size();
            const auto& pGroup = groups[res[p][pIdx]];
            const auto& qGroup = groups[res[q][qIdx]];
            resSize[p] -= pGroup.size();
            resSize[p] += qGroup.size();
            resSize[q] -= qGroup.size();
            resSize[q] += pGroup.size();
            swap(res[p][pIdx], res[q][qIdx]);
            if(resSize[p] > K || resSize[q] > K || !connected(res[p]) || !connected(res[q])){
                swap(res[p][pIdx], res[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
                continue;
            }
            double scoreDif = 0.0;
            for(int i=0;i<res[p].size();i++){
                if(i == pIdx) continue;
                scoreDif -= params[res[p][i]][res[q][qIdx]];
                scoreDif += params[res[p][i]][res[p][pIdx]];
            }
            for(int i=0;i<res[q].size();i++){
                if(i == qIdx) continue;
                scoreDif -= params[res[q][i]][res[p][pIdx]];
                scoreDif += params[res[q][i]][res[q][qIdx]];
            }
            if(scoreDif < 0.0 || bernoulli_distribution(exp(-scoreDif/temperature))(globalRandom)){
                scoreSum += scoreDif;
                showScore(tryNum);
            } else {
                swap(res[p][pIdx], res[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
            }
        } else {
            // move
            const int pIdx = globalRandom()%res[p].size();
            if(pIdx+1 != res[p].size()) swap(res[p][pIdx], res[p].back());
            const auto& pGroup = groups[res[p].back()];
            resSize[p] -= pGroup.size();
            resSize[q] += pGroup.size();
            res[q].push_back(res[p].back());
            res[p].pop_back();
            if(resSize[p] > K || resSize[q] > K || !connected(res[p]) || !connected(res[q])){
                res[p].push_back(res[q].back());
                res[q].pop_back();
                resSize[p] += pGroup.size();
                resSize[q] -= pGroup.size();
                continue;
            }
            double scoreDif = 0.0;
            for(int i=0;i<res[p].size();i++){
                scoreDif -= params[res[q].back()][res[p][i]];
            }
            for(int i=0;i+1<res[q].size();i++){
                scoreDif += params[res[q].back()][res[q][i]];
            }
            if(scoreDif < 0.0 || bernoulli_distribution(exp(-scoreDif/temperature))(globalRandom)){
                scoreSum += scoreDif;
                showScore(tryNum);
            } else {
                res[p].push_back(res[q].back());
                res[q].pop_back();
                resSize[p] += pGroup.size();
                resSize[q] -= pGroup.size();
            }
        }
    }
    return res;
}

//------------------------------------------------------------------------------
vector<pair<double, double>> getEdgeDir(const vector<Edge>& edges, const vector<pair<int, int>>& coord){
    vector<pair<double, double>> dir;
    for(const auto& e : edges){
        double dx = coord[e.dst].first - coord[e.src].first;
        double dy = coord[e.dst].second - coord[e.src].second;
        const double len = sqrt(dx * dx + dy * dy);
        dx /= len;
        dy /= len;
        dir.emplace_back(dx, dy);
    }
    return dir;
}

//------------------------------------------------------------------------------
vector<vector<int>> splitEdges(const vector<vector<Node>>& g, const vector<Edge>& edges, const vector<pair<int,int>>& coord){
    const int upperSize = 10;
    const vector<pair<double, double>> dir = getEdgeDir(edges, coord);
    const int M = edges.size();
    vector<int> checked(M, 0);
    auto calcDot = [&](int src, int dst){
        double res = dir[src].first * dir[dst].first + dir[src].second * dir[dst].second;
        return (edges[src].src == edges[dst].src || edges[src].dst == edges[dst].dst) ? -res : res;
    };
    vector<vector<int>> groups;
    for(int i=0;i<M;i++){
        if(checked[i]) continue;
        vector<int> cur;
        cur.push_back(i);
        checked[i] = 1;
        int pos = edges[i].dst;
        for(int k=0;k<2;k++){
            while(cur.size() < upperSize){
                if(g[pos].size() <= 2) break;
                int nextIdx = -1;
                double bestDot = 0.7;
                for(int nodeIdx=0;nodeIdx<g[pos].size();nodeIdx++){
                    if(nodeIdx == g[pos].size()) nodeIdx = 0;
                    const int dstIdx = g[pos][nodeIdx].idx;
                    if(!checked[dstIdx]){
                        double d = calcDot(cur.back(), dstIdx);
                        if(d > bestDot){
                            bestDot = d;
                            nextIdx = nodeIdx;
                        }
                    }
                }
                if(nextIdx == -1) break;
                const int dstIdx = g[pos][nextIdx].idx;
                checked[dstIdx] = 1;
                cur.push_back(dstIdx);
                pos = g[pos][nextIdx].pos;
            }
            if(cur.size() == upperSize) break;
            if(k == 0){
                reverse(cur.begin(), cur.end());
                pos = edges[i].src;
            }
        }
        groups.emplace_back(cur);
    }
    return groups;
}

//------------------------------------------------------------------------------
vector<vector<int>> generateSolutionFromGroups(vector<vector<Node>>& g,
                                               const vector<Edge>& edges,
                                               const vector<pair<int,int>>& coord,
                                               const vector<pair<int,int>>& edgeIdx,
                                            //    const vector<vector<int>>& baseCost,
                                               const vector<Edge>& dual,
                                               const vector<vector<int>>& groups,
                                               const Timer& timer,
                                               int N, int M, int D, int K)
{
    int dualSize = 0;
    for(auto& e : dual){
        dualSize = max(dualSize, max(e.src, e.dst)+1);
    }

    auto calcScore = [&](const vector<int>& groupList){
        UnionFind uf(dualSize);
        int res = 0;
        for(const auto& groupIdx : groupList){
            for(const auto& t : groups[groupIdx]){
                const int p = uf.getRoot(dual[t].src);
                const int q = uf.getRoot(dual[t].dst);
                if(p == q) ++res;
                else uf.merge(p, q);
            }
        }
        return res;
    };

    vector<int> order(groups.size());
    for(int i=0;i<groups.size();i++) order[i] = i;
    shuffle(order.begin(), order.end(), globalRandom);
    vector<vector<int>> resGroups(D);
    vector<int> resSize(D, 0);
    for(int i=0;i<groups.size();i++){
        int p = 0;
        for(int j=1;j<resSize.size();j++) if(resSize[p] > resSize[j]) p = j;
        resGroups[p].push_back(order[i]);
        resSize[p] += groups[order[i]].size();
    }
    int scoreSum = 0;
    vector<int> scores(D);
    for(int i=0;i<D;i++){
        scores[i] = calcScore(resGroups[i]) + max(resSize[i] - K, 0);
        scoreSum += scores[i];
    }
    vector<int> separates(D);
    int trynum = 0;
    while(timer.msec() < 4500 && scoreSum > 0){
        ++trynum;
        int sepNum = 0;
        for(int i=0;i<D;i++) if(scores[i]) separates[sepNum++] = i;
        int p = separates[globalRandom()%sepNum];
        int q = globalRandom()%D;
        while(p == q || !resSize[q]){
            q = globalRandom()%D;
        }
        // if(true){
        if(globalRandom()%8){
            // swap
            const int pIdx = globalRandom()%resGroups[p].size();
            const int qIdx = globalRandom()%resGroups[q].size();
            const auto& pGroup = groups[resGroups[p][pIdx]];
            const auto& qGroup = groups[resGroups[q][qIdx]];
            resSize[p] -= pGroup.size();
            resSize[p] += qGroup.size();
            resSize[q] -= qGroup.size();
            resSize[q] += pGroup.size();
            swap(resGroups[p][pIdx], resGroups[q][qIdx]);
            int np = calcScore(resGroups[p]) + max(resSize[p]-K, 0);
            int nq = calcScore(resGroups[q]) + max(resSize[q]-K, 0);
            if(np+nq > scores[p]+scores[q]){
                swap(resGroups[p][pIdx], resGroups[q][qIdx]);
                resSize[p] += pGroup.size();
                resSize[p] -= qGroup.size();
                resSize[q] += qGroup.size();
                resSize[q] -= pGroup.size();
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
            }
        } else {
            // move
            const int pIdx = globalRandom()%resGroups[p].size();
            if(pIdx+1 != resGroups[p].size()) swap(resGroups[p][pIdx], resGroups[p].back());
            const auto& pGroup = groups[resGroups[p].back()];
            resSize[p] -= pGroup.size();
            resSize[q] += pGroup.size();
            resGroups[q].push_back(resGroups[p].back());
            resGroups[p].pop_back();
            int np = calcScore(resGroups[p]) + max(resSize[p]-K, 0);
            int nq = calcScore(resGroups[q]) + max(resSize[q]-K, 0);
            if(np+nq > scores[p]+scores[q]){
                resGroups[p].push_back(resGroups[q].back());
                resGroups[q].pop_back();
                resSize[q] -= pGroup.size();
                resSize[p] += pGroup.size();
            } else {
                scoreSum += np + nq - scores[p] - scores[q];
                scores[p] = np;
                scores[q] = nq;
            }
        }
    }
    cerr << "trynum: " << trynum << " " << scoreSum << endl;
    // {
    //         vector<vector<int>> res;
    //     for(const auto& group : resGroups){
    //         vector<int> cur;
    //         for(const auto& idx : group){
    //             for(const auto& t : groups[idx]) cur.push_back(t);
    //         }
    //         res.emplace_back(cur);
    //     }
    //     cerr << "before: " << ::calcScore(g, edges, edgeIdx, baseCost, res) << endl;
    // }
    // resGroups = improveSolutionBFS(g, edges, edgeIdx, dual, groups, resGroups, timer, K, dualSize);
    resGroups = improveSolutionBFS2(g, edges, coord, edgeIdx, dual, groups, resGroups, timer, K, dualSize);
    vector<vector<int>> res;
    for(const auto& group : resGroups){
        vector<int> cur;
        for(const auto& idx : group){
            for(const auto& t : groups[idx]) cur.push_back(t);
        }
        res.emplace_back(cur);
    }
    // cerr << "after: " << ::calcScore(g, edges, edgeIdx, baseCost, res) << endl;
    return res;
}

//------------------------------------------------------------------------------
vector<vector<int>> generateSolutionFromGroups(vector<vector<Node>>& g,
                                               const vector<Edge>& edges,
                                               const vector<pair<int,int>>& coord,
                                               const vector<pair<int,int>>& edgeIdx,
                                            //    const vector<vector<int>>& baseCost,
                                               const vector<Edge>& dual,
                                               const Timer& timer,
                                               int N, int M, int D, int K)
{
    int dualSize = 0;
    for(auto& e : dual){
        dualSize = max(dualSize, max(e.src, e.dst)+1);
    }
    auto groups = splitEdges(g, edges, coord);

    auto calcScore = [&](const vector<int>& groupList){
        UnionFind uf(dualSize);
        int res = 0;
        for(const auto& groupIdx : groupList){
            for(const auto& t : groups[groupIdx]){
                const int p = uf.getRoot(dual[t].src);
                const int q = uf.getRoot(dual[t].dst);
                if(p == q) ++res;
                else uf.merge(p, q);
            }
        }
        return res;
    };

    vector<int> additionalGroups;
    for(int i=0;i<groups.size();i++){
        const auto& group = groups[i];
        vector<int> groupList(1, i);
        if(calcScore(groupList)){
            cerr << "error:";
            for(auto& t : group) cerr << " " << t;
            cerr << endl;
            // for now
            while(groups[i].size() >= 2){
                additionalGroups.push_back(groups[i].back());
                groups[i].pop_back();
            }
        }
    }
    for(auto& t : additionalGroups) groups.emplace_back(1, t);
    return generateSolutionFromGroups(g, edges, coord, edgeIdx, /*baseCost,*/ dual, groups, timer, N, M, D, K);
}

//------------------------------------------------------------------------------
vector<Edge> generateDualGraph(const vector<vector<Node>>& g, const vector<Edge>& edges, const vector<pair<int,int>>& coord){
    UnionFind uf(2*edges.size());
    for(int i=0;i<g.size();i++){
        vector<pair<double, int>> vp;
        const auto& ps = coord[i];
        for(int j=0;j<g[i].size();j++){
            const auto& pd = coord[g[i][j].pos];
            const double dx = pd.first - ps.first;
            const double dy = pd.second - ps.second;
            vp.emplace_back(atan2(dy, dx), j);
        }
        sort(vp.begin(), vp.end());
        for(int j=0;j<vp.size();j++){
            int s = vp[j].second;
            int d = vp[(j+1)%vp.size()].second;
            int es = 2 * g[i][s].idx;
            int ed = 2 * g[i][d].idx;
            if(edges[g[i][s].idx].src == i) ++es;
            if(edges[g[i][d].idx].dst == i) ++ed;
            uf.merge(es, ed);
        }
    }
    vector<int> idxMap(2*edges.size(), -1);
    int curIdx = 0;
    for(int i=0;i<2*edges.size();i++){
        int p = uf.getRoot(i);
        if(idxMap[p] != -1) continue;
        idxMap[p] = curIdx++;
    }
    vector<Edge> res;
    for(int i=0;i<2*edges.size();i+=2){
        const int p = idxMap[uf.getRoot(i)];
        const int q = idxMap[uf.getRoot(i+1)];
        res.emplace_back(p, q, edges[i/2].weight);
    }
    return res;
}

//------------------------------------------------------------------------------
int main(int argc, const char* argv[]){
    Timer timer;
    int N, M, D, K; cin >> N >> M >> D >> K;
    vector<vector<Node>> g(N);
    vector<Edge> edges;
    vector<pair<int,int>> edgeIdx;
    vector<pair<int,int>> coord;
    for(int i=0;i<M;i++){
        int p, q, w; cin >> p >> q >> w;
        --p; --q;
        edgeIdx.emplace_back(g[p].size(), g[q].size());
        g[p].emplace_back(q, w, i);
        g[q].emplace_back(p, w, i);
        edges.emplace_back(p, q, w);
    }
    for(int i=0;i<N;i++){
        int x, y; cin >> x >> y;
        coord.emplace_back(x, y);
    }
    auto dual = generateDualGraph(g, edges, coord);
    auto res = generateSolutionFromGroups(g, edges, coord, edgeIdx, /*baseCost,*/ dual, timer, N, M, D, K);
    cerr << timer.msec() << endl;

    printSolution(res, M);
    auto baseCost = allDistance(g);
    cerr << calcScore(g, edges, edgeIdx, baseCost, res) << endl;
}
