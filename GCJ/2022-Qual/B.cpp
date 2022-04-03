#include <iostream>
#include <numeric>

using namespace std;

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        cout << "Case #" << test << ":";
        int arr[4] = {1000000, 1000000, 1000000, 1000000};
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                int t; cin >> t;
                arr[j] = min(arr[j], t);
            }
        }
        int s = accumulate(arr, arr+4, 0);
        if(s < 1000000){
            cout << " IMPOSSIBLE" << endl;
        } else {
            int rest = 1000000;
            for(int i=0;i<4;i++){
                cout << " " << min(rest, arr[i]);
                rest = max(0, rest-arr[i]);
            }
            cout << endl;
        }
    }
}