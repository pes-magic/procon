#include <iostream>
#include <string>

using namespace std;

int main(){
    int N;
    string a;
    cin >> N >> a;
    auto isOdd = [&](){
        int res = 0;
        for(int i=0;i<N;i++){
            if(a[i] == '2' && ((N-1)&i) == i) res = 1-res;
        }
        return res;
    };
    if(a.find('2') != string::npos){
        cout << (isOdd() ? 1 : 0) << endl;
    } else {
        for(auto& c : a) if(c == '3') c = '2';
        cout << (isOdd() ? 2 : 0) << endl;
    }
}