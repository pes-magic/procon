#include <iostream>
#include <vector>

using namespace std;

int main(){
    int A, B; cin >> A >> B;
    vector d(A, vector(B, 0));
    for(auto& v : d){
        for(auto& t : v) cin >> t;
    }
    int ofs[101][101];
    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            ofs[i][j] = 0;
            for(int a=1;a<=A;a++){
                for(int b=1;b<=B;b++){
                    ofs[i][j] = max(ofs[i][j], d[a-1][b-1]-(i*a+j*b));
                }
            }
        }
    }
    bool ok = true;
    for(int a=1;a<=A;a++){
        for(int b=1;b<=B;b++){
            int r = 10000;
            for(int i=0;i<=100;i++){
                for(int j=0;j<=100;j++){
                    r = min(r, i*a+j*b+ofs[i][j]);
                }
            }
            if(r != d[a-1][b-1]) ok = false;
        }
    }
    if(ok){
        cout << "Possible" << endl;
        cout << 300 << " " << 200 + 101*101 << endl;
        for(int i=1;i<=100;i++){
            cout << i << " " << i+1 << " X" << endl;
            cout << 151+i << " " << 150+i << " Y" << endl;
        }
        for(int i=0;i<=100;i++){
            for(int j=0;j<=100;j++){
                cout << i+1 << " " << j+151 << " " << ofs[i][j] << endl;
            }
        }
        cout << 1 << " " << 151 << endl;
    } else {
        cout << "Impossible" << endl;
    }
}