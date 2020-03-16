#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> a(N);
        for(auto& t : a){ cin >> t; --t; }
        int res = 0;
        for(int i=0;i<N;i++){
            if(i == a[a[i]]) ++res;
        }
        cout << (res/2) << endl;
    }
}