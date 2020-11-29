#include <iostream>

using namespace std;

int main(){
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    if(a == b || a == b+1){
        cout << x << endl;
    } else if(a < b){
        cout << x + min(2*x, y) * (b-a) << endl;
    } else {
        cout << x + min(2*x, y) * (a-(b+1)) << endl;
    }
}