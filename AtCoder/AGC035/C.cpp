#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    if(!(N&(N-1))){
        cout << "No" << endl;
        return 0;
    }
    vector<int> add(N+1, 0);
    vector<int> a;
    if(N%2 == 0){
        for(int i=N-2;i>=2;i-=2){
            if(N^i > i){
                a.push_back(i+1);
                a.push_back(i);
                add[i] = add[i+1] = 1;
                a.push_back(N^i);
                a.push_back((N^i)+1);
                add[N^i] = add[(N^i)+1] = 1;
                break;
            }
        }
   }
   for(int i=2;i<=N;i++) if(!add[i]) a.push_back(i);
   if(N%2 == 0 && a.back() == N) a.pop_back();
   cout << "Yes" << endl;
   cout << 1 << " " << a[0] << endl;
   cout << 1 << " " << N+a[1] << endl;
   cout << a[1] << " " << N+1 << endl;
   bool checked = false;
   for(int i=1;i<a.size();i++){
       cout << a[i-1] << " " << a[i] << endl;
       cout << N+a[(i-1)^1] << " " << N+a[i^1] << endl;
       if(!checked && N%2 == 0 && (a[i-1]^a[i]) == N){
           checked = true;
           cout << N << " " << a[i-1] << endl;
           cout << 2*N << " " << a[i] << endl;
       }
   }
}