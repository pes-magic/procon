#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<pair<int,int>> A;
        for(int i=0;i<N;i++){
            int a; cin >> a;
            A.emplace_back(a, i);
        }
        sort(A.begin(), A.end());
        int res = 0;
        for(int i=0;i<N;i++){
            if(A[i].second%2 != i%2) ++res;
        }
        cout << res/2 << endl;        
    }
}