#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    vector<int> v;
    for(int i=0;i<N;i++){
        if(S[i] == '#') v.push_back(i);
    }
    int x = v[0], y = N-1-v.back();
    for(int i=0;i+1<v.size();i++){
        if(x+y < v[i+1]-v[i]-1) x = v[i+1]-v[i]-1-y;
    }
    cout << x << " " << y << endl;
}