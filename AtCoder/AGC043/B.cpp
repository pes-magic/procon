#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	auto comb = [](int n, int r){
        int res = 1;
        while(n > 0 || r > 0){
            if(n%2 < r%2) return 0;
            n /= 2;
            r /= 2;
        }
        return 1;
	};
    int N;
    while(cin >> N){
        string S; cin >> S;
        for(auto& c : S) --c;
        auto isOdd = [&](){
            int res = 0;
            for(int i=0;i<N;i++){
                if(comb(N-1, i)) res = (res+S[i]-'0')%2;
            }
            return res == 1;
        };
        if(isOdd()){
            cout << 1 << endl;
        } else {
            if(any_of(S.begin(), S.end(), [](char c){ return c == '1'; })){
                cout << 0 << endl;
            } else {
                for(auto& c : S) if(c == '2') c = '1';
                cout << (isOdd() ? 2 : 0) << endl;
            }
        }
    }
}