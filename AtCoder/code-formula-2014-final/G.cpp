#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Block {
public:
    explicit Block(const vector<int>& v) : Block(){
        for(auto& t : v) push(t);
    }
    explicit Block() : minValue(1000000), maxValue(0) {}
    void push(int v){
        st.push(v);
        minValue = min(minValue, v);
        maxValue = max(maxValue, v);
    }
    int size() const { return st.size(); }
    int top() const { return st.top(); }
    void pop(){ st.pop(); }
    int minVal() const { return minValue; }
    int maxVal() const { return maxValue; }
private:
    int minValue;
    int maxValue;
    stack<int> st;
};

vector<pair<int, int>> solve(const vector<int>& r){
    vector<stack<Block>> pile(3);
    pile[0].emplace(r);
    vector<pair<int, int>> res;
    while(true){
        if(!pile[0].empty() || !pile[2].empty()){
            const int src = (!pile[0].empty() ? 0 : 2);
            const int dst = 2 - src;
            auto& b0 = pile[src].top();
            if(b0.size() == 1){
                if(src == 0 ) res.emplace_back(1, 3);
            } else {
                int thr = b0.minVal() + b0.size()/2 - 1;
                Block b1, b2;
                while(b0.size() > 0){
                    int v = b0.top(); b0.pop();
                    if(v <= thr){
                        b1.push(v);
                        res.emplace_back(src+1, 2);
                    } else {
                        b2.push(v);
                        res.emplace_back(src+1, dst+1);
                    }
                }
                pile[1].push(b1);
                pile[dst].push(b2);
            }
            pile[src].pop();
        } else if(!pile[1].empty()) {
            auto& b1 = pile[1].top();
            if(b1.size() == 1){
                res.emplace_back(2, 3);
                pile[1].pop();
            } else {
                Block b0;
                vector<int> b2;
                int thr = b1.minVal() + b1.size()/2 - 1;
                while(b1.size() > 0){
                    int v = b1.top(); b1.pop();
                    if(v <= thr){
                        res.emplace_back(2, 3);
                        b2.push_back(v);
                    } else {
                        res.emplace_back(2, 1);
                        b0.push(v);
                    }
                }
                pile[0].push(b0);
                pile[1].pop();
                for(int i=0;i<b2.size();i++) res.emplace_back(3, 2);
                reverse(b2.begin(), b2.end());
                pile[1].emplace(b2);
            }
        } else {
            break;
        }
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> r(N);
        for(auto& t : r) cin >> t;
        auto res = solve(r);
        cout << res.size() << endl;
        for(auto& p : res) cout << p.first << " " << p.second << endl;
    }
}