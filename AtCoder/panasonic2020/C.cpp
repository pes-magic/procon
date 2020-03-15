#include <iostream>

using namespace std;

int main(){
    long long a, b, c;
    while(cin >> a >> b >> c){
        auto check = [&](){
            auto d = c-a-b;
            if(d <= 0) return false;
            return 4*a*b < d*d;
        };
        cout << (check() ? "Yes" : "No") << endl;
    }
}