#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

double mem[100][100][100][2];

double search(int rest, int known, int all, int hit){
    if(rest == 0) return 0.0;
    if(mem[rest][known][all][hit] > -0.5) return mem[rest][known][all][hit];
    double res = 1.0;
    if(hit){
        if(known-1 > 0){
            res += (known-1.0)/(all-1.0) * search(rest-1, known-1, all-1, 1);
        }
        if(known < all){
            res += (all-known)/(all-1.0) * search(rest-1, known-1, all-1, 0);
        }
    } else {
        int d = all - known;
        if(known > 0){
            res += 1.0/d * known/(all-1.0) * search(rest-1, known, all-1, 1);
        }
        if(known < all-1){
            res += 1.0/d * (all-1-known)/(all-1.0) * search(rest-1, known, all-1, 0);
        }
        if(d > 1) res += (d-1.0)/d * (1 + search(rest, known+1, all, 0));
    }
    return mem[rest][known][all][hit] = res;
}

int main(){
    string S, K; cin >> S >> K;
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            for(int k=0;k<100;k++){
                mem[i][j][k][0] = mem[i][j][k][1] = -1;
            }
        }
    }
    int forget = 36 - K.size();
    int size = 0;
    vector<int> used(256, 0);
    for(auto& c : S){
        if(used[c]) continue;
        if(K.find(c) == string::npos){
            used[c] = 1;
            ++size;
        }
    }
    printf("%.10lf\n", search(size, 0, forget, 0) + S.size() - size);
}