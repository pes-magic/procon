#include <iostream>
#include <vector>

using namespace std;

int main(){
    int H, W, A, B; cin >> H >> W >> A >> B;
    vector<vector<int>> v(H, vector<int>(W, 0));
    for(int i=0;i<B;i++){
        for(int j=A;j<W;j++) v[i][j] = 1;
    }
    for(int i=B;i<H;i++){
        for(int j=0;j<A;j++) v[i][j] = 1;
    }
    for(auto& r : v){
        for(auto& t : r) cout << t;
        cout << endl;
    }
}