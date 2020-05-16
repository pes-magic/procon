#include <iostream>
#include <vector>

using namespace std;

vector<int> generate(int N, int d){
    int arr[2][8] = {
        {0, 1, 3, 2, 2, 3, 1, 0},
        {0, 1, 3, 2, 2, 0, 1, 3}
    };
    vector<int> res(2);
    res[0] = 0;
    res[1] = 1;
    --d;
    for(int i=1;i+1<N;i+=2){
        vector<int> next;
        for(int j=0;j<res.size();j+=2){
            int use = (d > 0 && j+2 == res.size() ? 1 : 0);
            for(int k=0;k<8;k++) next.push_back(4*res[j+k/4] + arr[use][k]);
            if(use) d -= 2;
        }
        res = next;
    }
    if(N%2 == 0){
        vector<int> next;
        for(int j=0;j<res.size();j+=2){
            next.push_back(2*res[j]);
            next.push_back(2*res[j]+1);
            next.push_back(2*res[j+1]+1);
            next.push_back(2*res[j+1]);
        }
        res = next;
    }
    return res;
}

vector<int> solve(int N, int A, int B){
    vector<int> same;
    vector<int> dif;
    for(int i=0;i<N;i++){
        if((A&(1<<i)) == (B&(1<<i))) same.push_back(i);
        else dif.push_back(i);
    }
    if(dif.size()%2 == 0) return vector<int>();
    auto base = generate(N, dif.size());
    vector<int> res;
    for(auto& t : dif) same.push_back(t);
    for(auto& t : base){
        int v = 0;
        for(int i=0;i<same.size();i++){
            if((A>>same[i])%2 != (t>>i)%2) v |= 1 << same[i];
        }
        res.push_back(v);
    }
    return res;
}

int main(){
    int N, A, B; cin >> N >> A >> B;
    auto res = solve(N, A, B);
    if(res.empty()){
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << res[0];
        for(int i=1;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}