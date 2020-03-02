#include <iostream>
#include <vector>

using namespace std;

int main(){
    int A[9];
    while(cin >> A[0]){
        for(int i=1;i<9;i++) cin >> A[i];
        int N; cin >> N;
        for(int i=0;i<N;i++){
            int b; cin >> b;
            for(auto& t : A) if(t == b) t = 0;
        }
        bool ok = false;
        for(int i=0;i<3;i++){
            bool b = true;
            for(int j=0;j<3;j++){
                if(A[3*i+j]) b = false;
            }
            if(b) ok = true;
        }
        for(int i=0;i<3;i++){
            bool b = true;
            for(int j=0;j<3;j++){
                if(A[3*j+i]) b = false;
            }
            if(b) ok = true;
        }
        for(int i=0;i<1;i++){
            bool b = true;
            for(int j=0;j<3;j++){
                if(A[4*j]) b = false;
            }
            if(b) ok = true;
        }
        for(int i=2;i<3;i++){
            bool b = true;
            for(int j=0;j<3;j++){
                if(A[2*j+i]) b = false;
            }
            if(b) ok = true;
        }
        cout << (ok ? "Yes" : "No") << endl;
    }
}