#include <iostream>
#include <set>

using namespace std;

int main(){
    int size = 1;
    set<pair<int, int>> S;
    S.emplace(0, 0);
    for(int i=0;i<10;i++){
        int ofs = 2*size-1;
        auto next = S;
        for(auto& p : S){
            next.emplace(p.first+ofs, p.second);
            next.emplace(p.first+ofs, p.second+ofs);
        }
        S = next;
        size = 3*size-1;
    }
    cout << S.size() << endl;
    for(auto& p : S) cout << p.first << " " << p.second << endl;
}