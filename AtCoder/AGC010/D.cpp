#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b){ return a%b ? gcd(b, a%b) : b; }

bool win(const vector<int>& A){
    int even = count_if(A.begin(), A.end(), [](int t){ return t%2 == 0; });
    if(even%2 == 1) return true;
    if(even != A.size() - 1) return false;

    auto B = A;
    int g = B[0];
    for(auto& t : B){
        if(t%2 == 1){
            if(t == 1) return false;
            --t;
        }
        g = gcd(g, t);
    }
    for(auto& t : B) t /= g;
    return !win(B);
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        cout << (win(A) ? "First" : "Second") << endl;
    }
}