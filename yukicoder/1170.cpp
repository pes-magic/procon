#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int main(){
    int N, A, B;
    while(cin >> N >> A >> B){
        vector<int> x(N);
        map<int, int> mp;
        for(int i=0;i<N;i++){
            cin >> x[i];
            mp[x[i]] = i;
        }
        vector<int> res(N, 0);
        vector<int> root(N, -1);
        while(!mp.empty()){
            int r = mp.begin()->second;
            mp.erase(mp.begin());
            root[r] = r;
            queue<int> qu; qu.push(x[r]);
            while(!qu.empty()){
                int v = qu.front(); qu.pop();
                ++res[r];
                {
                    auto s = mp.lower_bound(v - B);
                    auto e = mp.lower_bound(v - A + 1);
                    if(s != e){
                        for(auto it=s;it!=e;it++){
                            qu.push(it->first);
                            root[it->second] = r;
                        }
                        mp.erase(s, e);
                    }
                }
                {
                    auto s = mp.lower_bound(v + A);
                    auto e = mp.lower_bound(v + B + 1);
                    if(s != e){
                        for(auto it=s;it!=e;it++){
                            qu.push(it->first);
                            root[it->second] = r;
                        }
                        mp.erase(s, e);
                    }
                }
            }
        }
        for(int i=0;i<N;i++) cout << res[root[i]] << endl;
    }
}