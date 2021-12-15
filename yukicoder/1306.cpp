#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N; cin >> N;
    vector<pair<int, int>> dif(N*(N-1));
    dif[0] = make_pair(0, 0);
    for(int i=1;i<dif.size();i++){
        cout << "? " << i+1 << " " << 1 << endl;
        cin >> dif[i].first >> dif[i].second;
    }
    vector<int> res(N*(N-1), -1);
    vector<vector<int>> use(N, vector<int>(N, 0));
    for(int i=0;i<N;i++) use[0][i] = 1;
    auto minIdx = distance(dif.begin(), min_element(dif.begin(), dif.end()));
    auto maxIdx = distance(dif.begin(), max_element(dif.begin(), dif.end()));
    res[maxIdx] = (N-1)*N+N-1;
    use[N-1][N-1] = 1;
    res[minIdx] = N;
    use[1][0] = 1;
    for(int i=1;i<N;i++){
        if(res[0] != -1) break;
        for(int j=0;j<N;j++){
            if(use[i][j]) continue;
            int p1 = 1-i, q1 = -j;
            if(p1 > q1) swap(p1, q1);
            int p2 = N-1-i, q2 = N-1-j;
            if(p2 > q2) swap(p2, q2);
            if(dif[minIdx] == make_pair(p1, q1) && dif[maxIdx] == make_pair(p2, q2)){
                res[0] = i*N+j;
                use[i][j] = 1;
                break;
            }
        }
    }
    int a0 = res[0]/N, b0 = res[0]%N;
    for(int i=1;i<dif.size();i++){
        if(res[i] != -1) continue;
        vector<pair<int, int>> cand;
        int p = dif[i].first + a0, q = dif[i].second + b0;
        if(1 <= p && p <= N-1 && 0 <= q && q <= N-1 && !use[p][q]) cand.emplace_back(p, q);
        p = dif[i].second + a0, q = dif[i].first + b0;
        if(1 <= p && p <= N-1 && 0 <= q && q <= N-1 && !use[p][q]) cand.emplace_back(p, q);
        if(cand.size() == 2 && cand[0] == cand[1]) cand.pop_back();
        if(cand.size() == 2){
            int target = (a0 == b0 ? minIdx : maxIdx);
            cout << "? " << i+1 << " " << target+1 << endl;
            int p, q; cin >> p >> q;
            int pc = cand[0].first - res[target]/N;
            int qc = cand[0].second - res[target]%N;
            if(pc > qc) swap(pc, qc);
            if(p != pc || q != qc) swap(cand[0], cand[1]);
        }
        res[i] = cand[0].first * N + cand[0].second;
        use[cand[0].first][cand[0].second] = 1;
    }
    cout << "!";
    for(auto& t : res) cout << " " << t;
    cout << endl;
}