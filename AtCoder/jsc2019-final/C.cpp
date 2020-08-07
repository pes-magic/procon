#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    int N, L, X; cin >> N >> L >> X;
    set<int> S;
    multiset<int> pos;
    multiset<int> len;
    S.insert(X);
    pos.insert(min(X, L-X));
    len.insert(L);
    for(int i=0;i<N;i++){
        int A; cin >> A;
        int a = min(A, L-A);
        bool rem = S.count(A);
        auto update = [&](int val, bool add){
            if(add) len.insert(val);
            else len.erase(len.find(val));
        };
        if(rem){
            S.erase(S.find(A));
            pos.erase(pos.find(a));
        }
        const auto it = pos.lower_bound(a);
        if(it != pos.end()){
            auto post = it; ++post;
            if(post != pos.end()){
                update(*post - a, !rem);
                if(it != pos.begin()){
                    auto pre = it; --pre;
                    update(*post - *pre, rem);
                }
            }
        }
        if(it != pos.begin()){
            auto pre1 = it; --pre1;
            if(it != pos.end())  update(*it - *pre1, !rem);
            if(pre1 != pos.begin()){
                auto pre2 = pre1; --pre2;
                if(it != pos.end()) update(*it - *pre2, rem);
                update(a - *pre2, !rem);
            }
        }
        if(!rem){
            S.insert(A);
            pos.insert(a);
        }
        {
            auto it = pos.end(); --it;
            auto it2 = it; --it2;
            cout << min(*len.begin(), L-*it-*it2) << endl;
        }
    }
}