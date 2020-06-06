#include <iostream>
#include <vector>
#include <string>

using namespace std;

string s[5] = {
    ".###..#..###.###.#.#.###.###.###.###.###.",
    ".#.#.##....#...#.#.#.#...#.....#.#.#.#.#.",
    ".#.#..#..###.###.###.###.###...#.###.###.",
    ".#.#..#..#.....#...#...#.#.#...#.#.#...#.",
    ".###.###.###.###...#.###.###...#.###.###."
};

int main(){
    int N; cin >> N;
    vector<string> vs(5);
    for(auto& t : vs) cin >> t;
    for(int i=0;i<4*N;i+=4){
        for(int j=0;j<10;j++){
            bool ok = true;
            for(int k=0;k<5;k++){
                for(int l=0;l<4;l++){
                    if(vs[k][i+l] != s[k][4*j+l]) ok = false;
                }
            }
            if(ok) cout << j;
        }
    }
    cout << endl;
}