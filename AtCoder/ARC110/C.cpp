#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> P(N);
    vector<int> pos(N);
    for(int i=0;i<N;i++){
        cin >> P[i];
        --P[i];
        pos[P[i]] = i;
    }
    vector<int> op;
    vector<int> used(N, 0);
    for(int i=0;i<N;i++){
        if(pos[i] == i) continue;
        for(int j=pos[i];j>i;j--){
            if(used[j]) break;
            used[j] = 1;
            op.push_back(j);
            swap(P[j], P[j-1]);
            pos[P[j]] = j;
            pos[P[j-1]] = j-1;
        }
    }
    bool valid = (op.size() == N-1);
    for(int i=0;i<N;i++) if(P[i] != i) valid = false;
    if(valid){
        for(auto& t : op) cout << t << endl;
    } else {
        cout << -1 << endl;
    }
}