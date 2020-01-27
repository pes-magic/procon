#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> grundy(101, 0);
    for(int i=2;i<=100;i++){
        vector<int> v(101, 0);
        for(int j=2;j<=i;j++){
            if(i%j) continue;
            v[grundy[i/j]] = 1;
        }
        for(int j=0;j<=100;j++){
            if(!v[j]){
                grundy[i] = j;
                break;
            }
        }
    }
    int N;
    while(cin >> N){
        int cur = 0;
        for(int i=0;i<N;i++){
            int A; cin >> A;
            cur ^= grundy[A];
        }
        cout << (cur ? "Yes" : "No") << endl;
    }
}