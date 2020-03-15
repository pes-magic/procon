#include <iostream>
#include <cmath>

using namespace std;

long long solve(long long a, long long b, long long c, long long d){
    long long res = abs(a-c) + abs(b-d);
    auto calc = [](long long x1, long long y1, long long x2, long long y2){
        auto sx = x1, sy = y1, gx = x2, gy = y2; 
        long long res = 0;
        long long block = 1;
        for(int i=0;i<30;i++){
            if(sx == gx && sx%3 == 1 && abs(sy - gy) >= 2){
                long long c1 = x1 % block;
                long long c2 = x2 % block;
                res = max(res, min(c1+c2+2, 2*block-c1-c2) + abs(y1 - y2));
            }
            sx /= 3;
            sy /= 3;
            gx /= 3;
            gy /= 3;
            block *= 3;
        }
        return res;
    };
    return max(res, max(calc(a, b, c, d), calc(b, a, d, c)));
}

int main(){
    int Q;
    while(cin >> Q){
        while(Q--){
            long long a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << solve(a-1, b-1, c-1, d-1) << endl;
        }
    }
}