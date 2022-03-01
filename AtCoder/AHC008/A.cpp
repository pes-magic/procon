#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <queue>
#include <array>
#include <cstdio>

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

enum PetType {
    Cow = 0,
    Pig = 1,
    Rabbit = 2,
    Dog = 3,
    Cat = 4
};

class Pet {
public:
    int mPos, mKind;
};

class Human {
public:
    int mPos;
};

const int dpos[] = {-32, 32, -1, 1, 0};
const int INF = 1 << 30;

int getDirIdx(char c){
    static unordered_map<char, int> res = {{'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}, {'.', 4}};
    return res[c];
}

char getDir(int idx){
    return "UDLR."[idx];
}

// return (distance, direction idx for first step)
vector<int> getSteps(const vector<int>& wall, int start){
    vector<int> step(32*32, INF);
    step[start] = 0;
    queue<int> qu; qu.push(start);
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(int i=0;i<4;i++){
            int np = p + dpos[i];
            if(wall[np]) continue;
            if(step[np] <= step[p] + 1) continue;
            step[np] = step[p] + 1;
            qu.push(np);
        }
    }
    return step;
}

pair<int, int> getPath(const vector<int>& wall, int start, int goal){
    if(start == goal) return make_pair(0, 4);
    vector<int> step(32*32, INF);
    step[goal] = 0;
    queue<int> qu; qu.push(goal);
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(int i=0;i<4;i++){
            int np = p + dpos[i];
            if(wall[np]) continue;
            if(step[np] <= step[p] + 1) continue;
            step[np] = step[p] + 1;
            if(np == start) return make_pair(step[np], i^1);
            qu.push(np);
        }

    }
    return make_pair(-1, 4);
}

template<typename CAP, typename COST>
class MinCostFlow {
public:
    explicit MinCostFlow(int humanNum, int roomNum)
        : g(humanNum + roomNum + 2)
        , h(humanNum + roomNum + 2, 0)
        , humanNum(humanNum)
        , roomNum(roomNum)
    {
        for(int i=1;i<=humanNum;i++){
            addEdge(0, i, 1, 0);
        }
        for(int i=1;i<=roomNum;i++){
            addEdge(i+humanNum, humanNum+roomNum+1, 1, GOAL);
        }
    }
    void addEdge(int src, int dst, CAP cap, COST cost){
        int r1 = g[src].size();
        int r2 = g[dst].size();
        g[src].emplace_back(src, dst, cap, cost, r2);
        g[dst].emplace_back(dst, src, 0, -cost, r1);
    }
    void addEdge(int humanId, int roomId, COST cost){
        const int src = humanId + 1;
        const int dst = humanNum + roomId + 1;
        addEdge(src, dst, 1, cost);
    }
    void forceUseRoom(int roomId){
        auto& p = g[humanNum+roomId+1][0];
        auto& q = g[p.dst][p.rev];
        p.cost = q.cost = 0;
    }
    pair<COST, CAP> solve(int s, int t, CAP maxFlow){
        const int n = g.size();
        pair<COST, CAP> res = make_pair(0, 0);
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
        res.first %= GOAL;
        return res;
    }
    vector<int> getTargetRoom(){
        vector<int> res(humanNum, -1);
        for(int i=0;i<humanNum;i++){
            for(auto& p : g[i+1]){
                if(p.dst == 0) continue;
                if(p.cap == 0){
                    res[i] = p.dst - humanNum - 1;
                    break;
                }
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
    const COST GOAL = 1LL << 24;
    const COST INF = 1LL << 30;
    vector<vector<Edge>> g;
    vector<COST> h;
    const int humanNum;
    const int roomNum;
};

constexpr int toPos(int x, int y){ return 32 * x + y; }

constexpr array<int, 3> sep = {5, 15, 25};

vector<int> initialDesk(){
    vector<int> res(32*32, 0);
    auto onSep = [&](int t){
        for(auto& p : sep) if(p == t) return true;
        return false;
    };
    for(auto& p : sep){
        res[toPos(1, p-1)] = res[toPos(1, p+1)] = 1;
        res[toPos(30, p-1)] = res[toPos(30, p+1)] = 1;
    }
    for(int i=3;i<30;i+=3){
        int cnt = 0;
        for(int j=1;j<=30;j++){
            if(onSep(j)){
                ++cnt;
            } else if((j+cnt)%2){
                res[toPos(i, j)] = 1;
            }
        }
    }
    for(int i=4;i<30;i+=3){
        int cnt = 1;
        for(int j=1;j<=30;j++){
            if(onSep(j)){
                ++cnt;
            } else if((j+cnt)%2){
                res[toPos(i, j)] = 1;
            }
        }
    }
    return res;
}

vector<int> separateRoom(){
    auto res = initialDesk();
    for(int i=2;i<30;i+=3){
        for(auto& p : sep){
            res[toPos(i, p-1)] = res[toPos(i, p+1)] = 1;
        }
    }
    for(int i=0;i<32;i++){
        res[toPos(0, i)] = res[toPos(31, i)] = 1;
        res[toPos(i, 0)] = res[toPos(i, 31)] = 1;
    }
    return res;
}

UnionFind roomGroup(){
    const vector<int> wall = separateRoom();
    UnionFind res(32*32);
    for(int i=1;i<=30;i++){
        for(int j=1;j<=30;j++){
            const int p = toPos(i, j);
            if(wall[p]) continue;
            for(auto& dif : {1, 32}){
                if(wall[p+dif]) continue;
                res.merge(p, p+dif);
            }
        }
    }
    return res;
}

int calcScore(const vector<int>& wall, const vector<Human>& human, const vector<Pet>& pet){
    UnionFind uf(wall.size());
    for(int i=1;i<=30;i++){
        for(int j=1;j<=30;j++){
            const int p = toPos(i, j);
            if(wall[p]) continue;
            if(!wall[p+1]) uf.merge(p, p+1);
            if(!wall[p+32]) uf.merge(p, p+32);
        }
    }
    vector<double> petCnt(wall.size(), 1.0);
    for(auto& p : pet){
        int g = uf.getRoot(p.mPos);
        petCnt[g] *= 0.5;
    }
    double score = 0;
    for(auto& h : human){
        int g = uf.getRoot(h.mPos);
        score += uf.getSize(g) * petCnt[g];
    }
    score *= 1e8 / 900.0 / human.size();
    return (int)(score+0.5);
}

int main(){
    int N; cin >> N;
    vector<int> wall(32*32, 0);
    for(int i=0;i<32;i++){
        wall[toPos(0, i)] = wall[toPos(31, i)] = 1;
        wall[toPos(i, 0)] = wall[toPos(i, 31)] = 1;
    }
    vector<Pet> pet(N);
    vector<int> petNum(32*32, 0);
    for(auto& p : pet){
        int x, y;
        cin >> x >> y >> p.mKind;
        p.mPos = toPos(x, y);
        --p.mKind;
        ++petNum[p.mPos];
    }
    int M; cin >> M;
    vector<Human> human(M);
    vector<int> humanNum(32*32, 0);
    for(auto& h : human){
        int x, y;
        cin >> x >> y;
        h.mPos = toPos(x, y);
        ++humanNum[h.mPos];
    }
    // for initial settings
    vector<int> ready(32, 1);
    for(int i=0;i<10;i++) ready[3*i+1] = 0;
    ready[30] = 0;
    vector<int> line(M, -1);
    vector<int> targetPos(M, -1);
    auto deskTarget = initialDesk();
    vector<int> sepIdx(M+1, 1);
    for(int i=0;i<M;i++){
        sepIdx[i+1] = sepIdx[i] + (30+i)/M;
    }
    // for surrounding
    vector<int> targetRoom(M, -1);
    constexpr int cRoomNum = 10 * (sep.size() + 1);
    vector<int> roomPos(cRoomNum);
    vector<int> closedRoom(2*cRoomNum, 0);
    vector<int> closedTarget(2*cRoomNum, -1);
    for(int i=0;i<10;i++){
        roomPos[i*(sep.size()+1)] = toPos(3*i+2, sep[0]/2);
        for(int j=0;j+1<sep.size();j++){
            roomPos[i*(sep.size()+1)+j+1] = toPos(3*i+2, (sep[j]+sep[j+1])/2);
        }
        roomPos[i*(sep.size()+1)+sep.size()] = toPos(3*i+2, (sep.back()+30)/2);
        closedRoom[2*i*(sep.size()+1)] = 1;
        for(int j=0;j<sep.size();j++){
            closedTarget[2*i*(sep.size()+1)+2*j+1] = closedTarget[2*i*(sep.size()+1)+2*j+2] = toPos(3*i+2, sep[j]);
        }
        closedRoom[2*(i+1)*(sep.size()+1)-1] = 1;
    }
    auto ufRoom = roomGroup();
    vector<int> roomIdx(32*32, -1);
    for(int i=0;i<roomPos.size();i++){
        roomIdx[ufRoom.getRoot(roomPos[i])] = i;
    }
    vector<pair<int,int>> initOrder;
    for(int i=0;i<M;i++) initOrder.emplace_back(human[i].mPos, i);
    sort(initOrder.begin(), initOrder.end());
    int dogRoom = 4*(sep.size()+1) + 1;
    for(int turn=0;turn<300;turn++){
        auto canPutWall = [&](int p){
            if(humanNum[p]) return false;
            for(int k=0;k<5;k++){
                if(petNum[p + dpos[k]]) return false;
            }
            return true;
        };

        string move(M, '.');
        vector<int> decide(M, 0);
        if(turn == 299){
            const int curScore = calcScore(wall, human, pet);
            int bestScore = curScore;
            vector<int> bestMove(M, 4);
            for(int h1=0;h1<M;h1++){
                for(int m1=0;m1<4;m1++){
                    const int np1 = human[h1].mPos + dpos[m1];
                    if(wall[np1]) continue;
                    if(!canPutWall(np1)) continue;
                    wall[np1] = 1;
                    const int score = calcScore(wall, human, pet);
                    if(score > bestScore){
                        bestScore = score;
                        vector<int> curMove(M, 4);
                        curMove[h1] = m1;
                        bestMove = curMove;
                    }
                    for(int h2=h1+1;h2<M;h2++){
                        for(int m2=0;m2<4;m2++){
                            const int np2 = human[h2].mPos + dpos[m2];
                            if(wall[np2]) continue;
                            if(!canPutWall(np2)) continue;
                            wall[np2] = 1;
                            const int score = calcScore(wall, human, pet);
                            if(score > bestScore){
                                bestScore = score;
                                vector<int> curMove(M, 4);
                                curMove[h1] = m1;
                                curMove[h2] = m2;
                                bestMove = curMove;
                            }
                            for(int h3=h2+1;h3<M;h3++){
                                for(int m3=0;m3<4;m3++){
                                    const int np3 = human[h3].mPos + dpos[m3];
                                    if(wall[np3]) continue;
                                    if(!canPutWall(np3)) continue;
                                    wall[np3] = 1;
                                    const int score = calcScore(wall, human, pet);
                                    if(score > bestScore){
                                        bestScore = score;
                                        vector<int> curMove(M, 4);
                                        curMove[h1] = m1;
                                        curMove[h2] = m2;
                                        curMove[h3] = m3;
                                        bestMove = curMove;
                                    }
                                    wall[np3] = 0;
                                }
                            }
                            wall[np2] = 0;
                        }
                    }
                    wall[np1] = 0;
                }
            }
            cout << "# cur = " << curScore << endl;
            cout << "# best = " << bestScore << endl;
            if(bestScore > curScore){
                for(int i=0;i<M;i++){
                    move[i] = tolower(getDir(bestMove[i]));
                    decide[i] = 1;
                }
            }
        }
        for(auto& order : initOrder){
            const int i = order.second;
            if(targetRoom[i] != -1) continue;
            auto needWall = [&](int p){
                return deskTarget[p] && !wall[p];
            };
            if(line[i] != -1 && abs(ready[line[i]]) == 1){
                const int humanY = human[i].mPos%32;
                if(humanY == (ready[line[i]] == 1 ? (line[i]==1||line[i]==30?sep.back()+2:30) : (line[i]==1||line[i]==30)?sep[0]-2:1)){
                    const int checkPos1 = toPos(line[i], humanY - ready[line[i]]);
                    const int checkPos2 = toPos(line[i]-1, humanY);
                    if(!needWall(checkPos1) && !needWall(checkPos2)){
                        ready[line[i]] = 3;
                        if(line[i] == 30) ready[31] = 3;
                        line[i] = -1;
                    }
                }
            }
            if(line[i] == -1){
                for(int j=sepIdx[i];j<sepIdx[i+1];j++){
                    if(!ready[j]){
                        int t1 = toPos(j, (j==1 || j==30) ? sep[0]-2 : 1);
                        int t2 = toPos(j, (j==1 || j==30) ? sep.back()+2 : 30);
                        int d1 = getPath(wall, human[i].mPos, t1).first;
                        int d2 = getPath(wall, human[i].mPos, t2).first;
                        if(d1 == -1 && d2 == -1) continue;
                        if(d1 != -1 && (d2 == -1 || d1 < d2)){
                            ready[j] = 2;
                            targetPos[i] = t1;
                        } else {
                            ready[j] = -2;
                            targetPos[i] = t2;
                        }
                        line[i] = j;
                        break;
                    }
                }
            }
            if(line[i] == -1){
                continue;
            }
            if(abs(ready[line[i]]) == 2){
                int dir = getPath(wall, human[i].mPos, targetPos[i]).second;
                if(human[i].mPos == targetPos[i]){
                    targetPos[i] = -1;
                    ready[line[i]] /= 2;
                }
                move[i] = getDir(dir);
                ++humanNum[human[i].mPos + dpos[dir]];
                decide[i] = 1;
            } else {
                const int checkPos1 = toPos(line[i], human[i].mPos%32 - ready[line[i]]);
                const int checkPos2 = toPos(line[i] - 1, human[i].mPos%32);
                const bool b1 = needWall(checkPos1);
                const bool b2 = needWall(checkPos2);
                if(b1 || b2){
                    if(b1 && canPutWall(checkPos1)){
                        move[i] = (ready[line[i]] == 1 ? 'l' : 'r');
                        wall[checkPos1] = 1;
                    } else if(b2 && canPutWall(checkPos2)){
                        move[i] = 'u';
                        wall[checkPos2] = 1;
                    } else {
                        move[i] = '.';
                    }
                } else {
                    move[i] = (ready[line[i]] == 1 ? 'R' : 'L');
                    ++humanNum[human[i].mPos + dpos[getDirIdx(move[i])]];
                }
                decide[i] = 1;
            }
        }
        vector<int> roomPetNum(cRoomNum, 0);
        vector<int> roomHumanNum(cRoomNum, 0);
        vector<int> roomValue(cRoomNum, 0);
        vector<int> activePet(5, 0);
        vector<vector<int>> activeRoomPet(cRoomNum, vector<int>(5, 0));
        for(int i=1;i<=30;i++){
            for(int j=1;j<=30;j++){
                const int p = toPos(i, j);
                if(!petNum[p]) continue;
                int a = ufRoom.getRoot(p);
                if(roomIdx[a] == -1) continue;
                roomPetNum[roomIdx[a]] += petNum[p];
            }
        }
        for(int i=1;i<=30;i++){
            for(int j=1;j<=30;j++){
                const int p = toPos(i, j);
                if(!humanNum[p]) continue;
                int a = ufRoom.getRoot(p);
                if(roomIdx[a] == -1) continue;
                roomHumanNum[roomIdx[a]] += humanNum[p];
            }
        }
        for(int i=0;i<cRoomNum;i++){
            if(roomPetNum[i] == 0) continue;
            if(closedRoom[2*i] && closedRoom[2*i+1]) continue;
            roomValue[i] = min(4, roomPetNum[i]);
            if(closedRoom[2*i] || closedRoom[2*i+1]) roomValue[i] *= 2;
        }
        for(auto& p : pet){
            int room = roomIdx[ufRoom.getRoot(p.mPos)];
            if(room == -1 || !closedRoom[2*room] || !closedRoom[2*room+1]){
                ++activePet[p.mKind];
                if(room != -1) ++activeRoomPet[room][p.mKind];
            }
        }
        cout << "#";
        for(auto& t : activePet) cout << " " << t;
        cout << endl;

        // surround dog
        if(activePet[PetType::Dog] && dogRoom < cRoomNum && turn < 200){
            int canMove[2] = {-1, -1};
            for(int i=0;i<M;i++){
                if(decide[i]) continue;
                targetPos[i] = closedTarget[2*dogRoom+i%2];
                if(human[i].mPos != targetPos[i]){
                    int dir = getPath(wall, human[i].mPos, targetPos[i]).second;
                    if(human[i].mPos == targetPos[i]){
                        ready[line[i]] /= 2;
                    }
                    move[i] = getDir(dir);
                    ++humanNum[human[i].mPos + dpos[dir]];
                    decide[i] = 1;
                } else {
                    canMove[i%2] = i;
                }
            }
            if(canMove[0] != -1 && canMove[1] != -1 && roomPetNum[dogRoom] > 0 && canPutWall(closedTarget[2*dogRoom]+1) && canPutWall(closedTarget[2*dogRoom+1]-1)){
                move[canMove[0]] = 'r';
                wall[closedTarget[2*dogRoom]+1] = 1;
                decide[canMove[0]] = 1;
                closedRoom[2*dogRoom] = 1;
                move[canMove[1]] = 'l';
                wall[closedTarget[2*dogRoom+1]-1] = 1;
                decide[canMove[1]] = 1;
                closedRoom[2*dogRoom+1] = 1;
                dogRoom += (sep.size()+1);
            }
            if(dogRoom < cRoomNum){
                for(int i=0;i<M;i++){
                    if(decide[i]) continue;
                    targetPos[i] = closedTarget[2*dogRoom+i%2];
                    if(human[i].mPos != targetPos[i]){
                        int dir = getPath(wall, human[i].mPos, targetPos[i]).second;
                        if(human[i].mPos == targetPos[i]){
                            ready[line[i]] /= 2;
                        }
                        move[i] = getDir(dir);
                        ++humanNum[human[i].mPos + dpos[dir]];
                    }
                    decide[i] = 1;
                }
            }
        }

        // keep the root
        {
            for(int i=1;i<sep.size();i++){
                int open = -1;
                for(int j=0;j<10;j++){
                    if(closedRoom[2*j*(sep.size()+1) + 2*i] || closedRoom[2*j*(sep.size()+1) + 2*i+1]) continue;
                    if(open == -1) open = j;
                    else open = -2;
                }
                if(open >= 0){
                    closedRoom[2*open*(sep.size()+1) + 2*i] = closedRoom[2*open*(sep.size()+1) + 2*i+1] = 1;
                }
            }
        }
        // decide Target Room
        {
            vector<vector<int>> steps(M);
            for(int i=0;i<M;i++){
                if(decide[i]) continue;
                steps[i] = getSteps(wall, human[i].mPos);
            }
            // vector<int> dogOrCat;
            // for(int j=0;j<cRoomNum;j++){
            //     if(roomValue[j] == 0) continue;
            //     if(closedRoom[2*j] || closedRoom[2*j+1]) continue;
            //     const int l = j/(sep.size()+1);
            //     if(ready[3*l+1] != 3 || ready[min(30, 3*l+4)] != 3) continue;
            //     if(activeRoomPet[j][PetType::Dog] > 0 || activeRoomPet[j][PetType::Cat] > 0){
            //         dogOrCat.push_back(j);
            //     }
            // }

            auto createMCF = [&](){
                MinCostFlow<int, int> mcf(M, 2*cRoomNum);
                for(int i=0;i<M;i++){
                    if(decide[i]) continue;
                    for(int j=0;j<2*cRoomNum;j++){
                        if(closedRoom[j]) continue;
                        if(roomValue[j/2] == 0) continue;
                        // if(j%2 == 0){
                        //     if(!closedRoom[j+1] && (activeRoomPet[j/2][PetType::Dog] > 0 || activeRoomPet[j/2][PetType::Cat] > 0)){
                        //         // skip this room
                        //         j++;
                        //         continue;
                        //     }
                        // }
                        const int l = j/(2*(sep.size()+1));
                        if(ready[3*l+1] != 3 || ready[min(30, 3*l+4)] != 3) continue;
                        if(steps[i][closedTarget[j]] == INF) continue;
                        mcf.addEdge(i, j, steps[i][closedTarget[j]] * 24 / roomValue[j/2]);
                    }
                }
                return mcf;
            };

            auto setForceUseRoom = [&](MinCostFlow<int, int>& mcf, int roomId){
                for(int i=0;i<M;i++){
                    if(decide[i]) continue;
                    for(int j=2*roomId;j<2*roomId+2;j++){
                        if(steps[i][closedTarget[j]] == INF) continue;
                        cout << "# " << i << " " << j << endl;
                        mcf.addEdge(i, j, steps[i][closedTarget[j]] * 24 / roomValue[j/2]);
                    }
                }
                mcf.forceUseRoom(roomId);
            };

            auto mcf = createMCF();
            auto a = mcf.solve(0, M+2*cRoomNum+1, M);
            auto result = mcf.getTargetRoom();
            /*
            for(int room1=0;room1<dogOrCat.size();room1++){
                cout << "# room1=" << dogOrCat[room1] << endl;
                auto mcf2 = createMCF();
                setForceUseRoom(mcf2, dogOrCat[room1]);
                auto b = mcf2.solve(0, M+2*cRoomNum+1, M);
                cout << "# " << b.first << " " << b.second << endl;
                if(b.second > a.second || (b.second == a.second && b.first < a.second)){
                    a = b;
                    result = mcf2.getTargetRoom();
                }
                for(int room2=room1+1;room2<dogOrCat.size();room2++){
                    cout << "# room1=" << dogOrCat[room1] << ", room2=" << dogOrCat[room2] << endl;
                    auto mcf3 = createMCF();
                    cout << "# " << b.first << " " << b.second << endl;
                    setForceUseRoom(mcf3, dogOrCat[room1]);
                    setForceUseRoom(mcf3, dogOrCat[room2]);
                    b = mcf3.solve(0, M+2*cRoomNum+1, M);
                    if(b.second > a.second || (b.second == a.second && b.first < a.second)){
                        a = b;
                        result = mcf3.getTargetRoom();
                    }
                }
            }
            */
            for(int i=0;i<M;i++){
                if(decide[i]) continue;
                if(result[i] == -1){
                    targetRoom[i] = -1;
                    targetPos[i] = -1;
                } else {
                    targetRoom[i] = result[i];
                    targetPos[i] = closedTarget[result[i]];
                }
            }
        }
        for(int i=0;i<M;i++){
            if(decide[i]) continue;
            if(targetRoom[i] != -1) continue;
            int nearestSep = -1;
            int nearestDist = 100000;
            for(auto p : sep){
                int d = abs(p - human[i].mPos%32);
                if(d < nearestDist){
                    nearestDist = d;
                    nearestSep = p;
                }
            }
            if(nearestSep != -1){
                int nearestPetX = human[i].mPos/32;
                int nearestPetDist = 10000000;
                auto steps = getSteps(wall, human[i].mPos);
                for(auto& p : pet){
                    int room = roomIdx[ufRoom.getRoot(p.mPos)];
                    if(room == -1){
                        if(nearestPetDist > steps[p.mPos]){
                            nearestPetDist = steps[p.mPos];
                            nearestPetX = p.mPos/32;
                        }
                    }
                }
                targetRoom[i] = 2*cRoomNum;
                targetPos[i] = toPos(nearestPetX, nearestSep);
            }
        }
        for(int i=0;i<M;i++){
            if(decide[i]) continue;
            if(targetRoom[i] != -1){
                if(human[i].mPos != targetPos[i]){
                    int dir = getPath(wall, human[i].mPos, targetPos[i]).second;
                    if(human[i].mPos == targetPos[i]){
                        ready[line[i]] /= 2;
                    }
                    move[i] = getDir(dir);
                    ++humanNum[human[i].mPos + dpos[dir]];
                    decide[i] = 1;
                } else if(targetRoom[i] == 2*cRoomNum){
                    targetRoom[i] = -1;
                }
            }
        }

        for(int i=0;i<M;i++){
            if(decide[i]) continue;
            if(targetRoom[i] != -1){
                if(human[i].mPos != targetPos[i]) continue;
                int wp = targetPos[i] + (targetRoom[i]%2 ? -1 : 1);
                if(canPutWall(wp)){
                    move[i] = (targetRoom[i]%2 ? 'l' : 'r');
                    wall[wp] = 1;
                    decide[i] = 1;
                    if(targetRoom[i] != closedRoom.size()){
                        closedRoom[targetRoom[i]] = 1;
                    }
                    targetRoom[i] = -1;
                    targetPos[i] = -1;
                }
            }
        }
        if(turn == 299){
            cout << "# " << calcScore(wall, human, pet) << endl;
        }
        cout << move << endl;
        for(int i=0;i<M;i++){
            if(!isupper(move[i])) continue;
            --humanNum[human[i].mPos];
            human[i].mPos += dpos[getDirIdx(move[i])];
            // ++humanNum[human[i].mPos];
        }
        string s;
        for(int i=0;i<N;i++){
            cin >> s;
            --petNum[pet[i].mPos];
            for(auto& c : s){
                pet[i].mPos += dpos[getDirIdx(c)];
            }
            ++petNum[pet[i].mPos];
        }
    }
}