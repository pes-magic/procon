#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        if((N&(N-1)) == 0){
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        vector<int> l(1, 1);
        vector<int> r(1, 1);
        vector<int> checked(N+1, 0);
        bool checkN = (N%2 == 1);
        for(int i=2;i+1<=N;i+=2){
            if(checked[i]) continue;
            l.push_back(i);
            l.push_back(i+1);
            r.push_back(N+i+1);
            r.push_back(N+i);
            if(!checkN && N%2 == 0 && (N^i) < N){
                int b = (N^i);
                checked[b] = 1;
                checkN = true;
                l.push_back(b+1);
                l.push_back(b);
                r.push_back(N+b);
                r.push_back(N+b+1);
                cout << N << " " << N+i << endl;
                cout << 2*N << " " << N+b << endl;
            }
        }
        for(int i=0;i+1<l.size();i++) cout << l[i] << " " << l[i+1] << endl;
        for(int i=0;i+1<r.size();i++) cout << r[i] << " " << r[i+1] << endl;
        cout << 3 << " " << N+1 << endl;
    }
}