#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, Q; cin >> N >> Q;
    vector<int> root(N, -1);
    vector<int> parent(N, -1);
    vector<int> child(N, -1);
    vector<int> tail(N, -1);
    for(int i=0;i<N;i++) root[i] = tail[i] = i;
    for(int i=0;i<Q;i++){
        int f, t, x; cin >> f >> t >> x;
        --f; --t; --x;
        if(root[f] == x){
            if(root[t] == -1){
                root[t] = root[f];
                tail[t] = tail[f];
            } else {
                parent[x] = tail[t];
                child[tail[t]] = x;
                tail[t] = tail[f];
            }
            root[f] = tail[f] = -1;
        } else {
            if(root[t] == -1){
                root[t] = x;
                tail[t] = tail[f];
                tail[f] = parent[x];
                parent[x] = -1;
                child[tail[f]] = -1;
            } else {
                int tf = tail[f];
                tail[f] = parent[x];
                child[tail[f]] = -1;
                parent[x] = tail[t];
                child[tail[t]] = x;
                tail[t] = tf;
            }
        }
    }
    vector<int> res(N, -1);
    for(int i=0;i<N;i++){
        if(root[i] == -1) continue;
        int p = root[i];
        while(p != -1){
            res[p] = i;
            p = child[p];
        }
    }
    for(int i=0;i<N;i++) cout << res[i]+1 << endl;
}