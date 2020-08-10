#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    vector<long long> cnt(45*20*10, 0);
    for(int i=0;i<N;i++){
        string s; cin >> s;
        long long v = 0;
        int a = -1;
        for(auto& c : s){
            if(c == '.') a = 0;
            else {
                v = 10 * v + c - '0';
                if(a >= 0) ++a;
            }
        }
        int p2 = 0, p5 = 0;
        while(v%2 == 0){ p2++; v /= 2; }
        while(v%5 == 0){ p5++; v /= 5; }
        cnt[(p2*20+p5)*10+max(0, a)]++;
    }
    long long res = 0;
    for(int i=0;i<cnt.size();i++){
        int a0 = i%10;
        int p5_0 = i/10%20;
        int p2_0 = i/10/20;
        if(min(p5_0, p2_0) >= a0)
            res += cnt[i]*(cnt[i]-1)/2;
        for(int j=i+1;j<cnt.size();j++){
            int a1 = j%10;
            int p5_1 = j/10%20;
            int p2_1 = j/10/20;
            if(min(p2_0+p2_1, p5_0+p5_1) >= a0+a1)
                res += cnt[i] * cnt[j];
        }
    }
    cout << res << endl;
}
