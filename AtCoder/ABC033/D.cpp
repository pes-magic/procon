#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int dot(pair<int, int> a, pair<int, int> b){ return a.first * b.first + a.second * b.second; }
int cross(pair<int, int> a, pair<int, int> b){ return a.first * b.second - a.second * b.first; }

int main(){
    int N;
    while(cin >> N){
        vector<int> x(N), y(N);
        for(int i=0;i<N;i++) cin >> x[i] >> y[i];
        long long a = 0, b = 0;
        for(int i=0;i<N;i++){
            vector<pair<double, pair<int, int>>> vp;
            for(int j=0;j<N;j++){
                if(i == j) continue;
                int dx = x[j] - x[i];
                int dy = y[j] - y[i];
                vp.emplace_back(atan2(dy, dx), make_pair(dx, dy));
            }
            sort(vp.begin(), vp.end());
            int idxA = 0, idxB = 0;
            for(int j=0;j<vp.size();j++){
                while(idxA < vp.size()){
                    int cr = cross(vp[j].second, vp[idxA].second);
                    int dt = dot(vp[j].second, vp[idxA].second);
                    if(dt < 0) break;
                    if(cr > 0 && dt == 0) ++a;
                    if(dt >= 0 && cr < 0) break;
                    ++idxA;
                }
                idxB = idxA;
                while(idxB < vp.size()){
                    int cr = cross(vp[j].second, vp[idxB].second);
                    int dt = dot(vp[j].second, vp[idxB].second);
                    if(cr < 0 && dt == 0) ++a;
                    if(dt >= 0) break;
                    ++idxB;
                }
                b += idxB - idxA;
            }
        }
        long long c = N*(N-1LL)*(N-2LL)/6 - a - b;
        cout << c << " " << a << " " << b << endl;
    }
}