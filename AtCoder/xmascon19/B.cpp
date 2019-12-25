#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve(int N, string c){
    vector<int> a;
    if(c == "="){
        for(int j=0;j<N;j++) a.push_back(j+1);
    } else if(c == "<"){
        if(N <= 2){
            cout << "Merry Christmas!" << endl;
            return;
        }
        a.push_back(1);
        for(int j=1;j<N;j++) a.push_back(a.back()+j);
    } else {
        if(N <= 7){
            cout << "Merry Christmas!" << endl;
            return;
        }
        if(N == 8){
            cout << "1 3 4 5 8 12 13 15" << endl;
            return;
        }
        if(N == 9){
            cout << "1 3 4 5 8 10 14 15 17" << endl;
            return;
        }
        if(N == 10){
            cout << "1 2 3 6 9 11 15 16 18 19" << endl;
            return;
        }
        a.push_back(1);
        for(int j=0;j<3;j++) a.push_back(a.back()+2);
        for(int j=0;j<(N-6)/2;j++) a.push_back(a.back()+3);
        a.push_back(a.back()+2);
        for(int j=0;j<N-8-(N-6)/2;j++) a.push_back(a.back()+3);
        for(int j=0;j<3;j++) a.push_back(a.back()+2);
    }
    cout << a[0];
    for(int i=1;i<N;i++) cout << " " << a[i];
    cout << endl;
}

int main(){
    int N;
    string c;
    while(cin >> N >> c){
        solve(N, c);
    }

    // N = 10;
    // while(true){
    //     vector<int> a(1, 1);
    //     for(int i=1;i<N;i++){a.push_back(a.back() + xor128()%4 + 1);}
    //     set<int> S, D;
    //     for(auto& s : a){
    //         for(auto& t : a){
    //             S.insert(s+t);
    //             D.insert(s-t);
    //         }
    //     }
    //     if(S.size() > D.size()){
    //         cout << N << endl;
    //         for(auto& t : a) cout << t << " "; cout << endl;
    //         for(int i=0;i<N-1;i++) cout << a[i+1]-a[i] << " "; cout << endl;
    //         N--;
    //     }
    // }
}