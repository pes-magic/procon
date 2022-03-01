#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

int main(){
    set<pair<string, int>> seen;
    map<pair<string, int>, pair<string, int>> prev;
    map<pair<string, int>, int> action;

    priority_queue<pair<string, int>, vector<pair<string, int>>, function<bool(pair<string, int>,pair<string, int>)>> qu(
        [](const pair<string, int>& a, const pair<string, int>& b){ return a.first.size() > b.first.size();}
    );
    seen.emplace("11", 0);
    qu.emplace("11", 0);
    while(!qu.empty()){
        auto state = qu.top(); qu.pop();
        string key = state.first;
        int side = state.second;
        string nk[2][3] = {{"211", "1", "2"}, {"2", "211", "1"}};
        if(key.empty()){
            vector<int> actions;
            while(prev.count(state)){
                actions.push_back(action[state]);
                state = prev[state];
            }
            cout << "DEAE";
            reverse(actions.begin(), actions.end());
            {
                string add[3] = {"EEAE", "EB", "EC"};
                for(auto& t : actions) cout << add[t];
            }
            cout << "D";
            reverse(actions.begin(), actions.end());
            {
                string add[3] = {"AE", "EBEE", "CE"};
                for(auto& t : actions) cout << add[t];
            }
            cout << "AD" << endl;
            break;
        }
        for(int i=0;i<3;i++){
            string s0 = key + nk[side][i];
            string& s1 = nk[1-side][i];
            bool ok = true;
            for(int j=0;j<min(s0.size(), s1.size());j++){
                if(s0[j] != s1[j]) ok = false;
            }
            if(!ok) continue;
            if(s0.size() > s1.size()){
                string nextKey = s0.substr(s1.size());
                auto nextState = make_pair(nextKey, side);
                if(seen.count(nextState)) continue;
                seen.insert(nextState);
                prev[nextState] = state;
                action[nextState] = i;
                qu.push(nextState);
            } else {
                string nextKey = s1.substr(s0.size());
                auto nextState = make_pair(nextKey, 1-side);
                if(seen.count(nextState)) continue;
                seen.insert(nextState);
                prev[nextState] = state;
                action[nextState] = i;
                qu.push(nextState);
            }
        }
    }
}