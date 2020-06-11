#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
    int H, W, h, w; cin >> H >> W >> h >> w;
    vector<vector<long long>> a(H, vector<long long>(W, 0));
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(i%h == h-1 && j%w == w-1){
                a[i][j] = -1000000000;
            } else if(i%h == 0 && j%w == 0){
                a[i][j] = 999999999 - h * w + 2;
            } else {
                a[i][j] = 1;
            }
        }
    }
    long long sum = 0;
    for(auto& v : a) sum = accumulate(v.begin(), v.end(), sum);
    if(sum > 0){
        cout << "Yes" << endl;
        for(auto& v : a){
            for(auto& t : v) cout << t << " ";
            cout << endl;
        }
    } else {
        cout << "No" << endl;
    }
}