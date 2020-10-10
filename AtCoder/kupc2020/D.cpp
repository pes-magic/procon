#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int t){
    for(int i=2;i*i<=t;i++) if(t%i==0) return false;
    return true;
}

int main(){
    int N; cin >> N;
    if(isPrime(N)){
        cout << "impossible" << endl;
        return 0;
    }
    if(N%2 == 0){
        cout << N/2 << endl;
        for(int i=0;i<N/2;i++){
            cout << 2 << " " << 1+2*i << " " << 2*N-1-2*i << endl;
        }
    } else {
        int d = 2;
        while(N%d != 0) d++;
        vector<int> used((N-1)/2+1, 0);
        vector<pair<int,int>> vp;
        int low = 1, high = 2;
        while(vp.size() < (d-1)/2){
            while(low < used.size() && used[low]) ++low;
            high = low+1;
            while(high < used.size() && used[high]) ++high;
            if(low + high >= used.size()) break;
            if(used[low+high]){ low = high; continue; }
            used[low] = used[high] = used[low+high] = 1;
            vp.emplace_back(low, high);
        }
        vector<vector<int>> v;
        int idx = 1;
        for(auto& p : vp){
            vector<int> v1, v2;
            v1.push_back(N+2*p.first);
            v1.push_back(N+2*p.second);
            v1.push_back(N-2*(p.first+p.second));
            v2.push_back(N-2*p.first);
            v2.push_back(N-2*p.second);
            v2.push_back(N+2*(p.first+p.second));
            long long sum = 3*N;
            long long target = (long long)N/d*N;
            while(sum < target){
                while(used[idx]) ++idx;
                v1.push_back(N-2*idx);
                v1.push_back(N+2*idx);
                ++idx;
                sum += 2*N;
            }
            sum = 3*N;
            while(sum < target){
                while(used[idx]) ++idx;
                v2.push_back(N-2*idx);
                v2.push_back(N+2*idx);
                ++idx;
                sum += 2*N;
            }
            v.push_back(v1);
            v.push_back(v2);
        }
        vector<int> v1; v1.push_back(N);
        while(idx < used.size()){
            if(!used[idx]){
                v1.push_back(N-2*idx);
                v1.push_back(N+2*idx);
            }
            ++idx;
        }
        v.push_back(v1);
        cout << v.size() << endl;
        for(auto& res : v){
            cout << res.size();
            for(auto& t : res) cout << " " << t;
            cout << endl;
        }
    }
}