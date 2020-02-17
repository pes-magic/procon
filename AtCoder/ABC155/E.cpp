#include <iostream>
#include <string>

using namespace std;

int main(){
    string N;
    while(cin >> N){
        N = "0" + N;
        int a = N.back() - '0', b = 11 - (N.back() - '0');
        for(int i=N.size()-2;i>=0;i--){
            int d = N[i] - '0';
            int na = min(a, b) + d;
            int nb = min(a + 11, b + 9) - d;
            a = na;
            b = nb;
        }
        cout << min(a, b) << endl;
    }
}