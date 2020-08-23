#include <iostream>
#include <string>

using namespace std;

string f(int v){
    cout << "? " << v << endl;
    string res; cin >> res;
    return res;
}

int main(){
    int L = 0, R = 1000;
    int query = 25;
    while(R-L > query){
        int mid = (L+R)/2;
        auto s = f(mid);
        --query;
        if(s[0] == 's'){
            L = mid;
            continue;
        }
        s = f(mid+1);
        --query;
        if(s[0] == 's'){
            L = mid+1;
        } else {
            R = mid;
        }
    }
    for(int i=L+1;i<R;i++){
        auto s = f(i);
        --query;
        if(s[0] == 's') L = i;
    }
    cout << "! " << L << endl;
}