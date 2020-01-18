#include <iostream>
#include <vector>

using namespace std;

int main(){
    int A[4];
    while(cin >> A[0] >> A[1] >> A[2] >> A[3]){
        vector<int> c(10, 0);
        for(auto& t : A) c[t] = 1;
        cout << (c[1] && c[4] && c[7] && c[9] ? "YES" : "NO") << endl;
    }
}