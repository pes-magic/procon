#include <iostream>
#include <vector>

using namespace std;

int main(){
    long long K;
    while(cin >> K){
        vector<long long> res(50, 49+(K+49)/50);
        long long n = (K+49)/50*50;
        while(n > K){
            int mIdx = 0;
            for(int i=1;i<50;i++) if(res[mIdx] < res[i]) mIdx = i;
            for(int i=0;i<50;i++){
                if(i == mIdx) res[i] -= 50;
                else res[i]++;
            }
            --n;
        }
        cout << 50 << endl;
        cout << res[0];
        for(int i=1;i<50;i++) cout << " " << res[i];
        cout << endl;
    }
}