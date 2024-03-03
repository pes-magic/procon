#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <set>
#include <tuple>
#include <chrono>
#include <functional>

using namespace std;

const int N = 30;

struct Action {
    int xyxy;

    Action(int x1, int y1, int x2, int y2) {
        xyxy = x1 | (y1 << 8) | (x2 << 16) | (y2 << 24);
    }

    tuple<int,int,int,int> decode() const {
        return {xyxy & 255, (xyxy >> 8) & 255, (xyxy >> 16) & 255, xyxy >> 24};
    }

    bool operator==(const Action& other) const {
        return xyxy == other.xyxy;
    }
};

class State {
public:
    State(): m_a(), m_actions() {}
    const bool operator < (const State& other) const{
        return m_eval < other.m_eval;
    }
    void get_input(){
        m_target = 0;
        m_eval = 0;
        for(int i=0;i<N;i++){
            m_a.emplace_back(vector<int>(i+1));
            for(int j=0;j<=i;j++){
                cin >> m_a[i][j];
                if(m_a[i][j] == 0){
                    m_target_x = i;
                    m_target_y = j;
                }
                m_eval += i * m_a[i][j];
            }
        }
    }
    bool can_move_left() const {
        if(m_target_x == 0) return false;
        if(m_target_y == 0) return false;
        return m_a[m_target_x-1][m_target_y-1] > m_a[m_target_x][m_target_y];
    }
    bool can_move_right() const {
        if(m_target_x == 0) return false;
        if(m_target_y == m_target_x) return false;
        return m_a[m_target_x-1][m_target_y] > m_a[m_target_x][m_target_y];
    }
    bool is_end_state() const {
        return m_target == N*(N+1)/2;
    }
    State swap_left(){
        State next = *this;
        next.swap_(-1);
        return next;
    }
    State swap_right(){
        State next = *this;
        next.swap_(0);
        return next;
    }
    int get_eval() const { return m_eval; }
    const vector<vector<int>>& get_state() const { return m_a; }
    const vector<Action>& get_actions() const { return m_actions; }
private:
    void swap_(int dif_y){
        m_eval -= m_a[m_target_x-1][m_target_y+dif_y] * (m_target_x-1);
        m_eval -= m_a[m_target_x][m_target_y] * m_target_x;
        m_eval += m_a[m_target_x-1][m_target_y+dif_y] * m_target_x;
        m_eval += m_a[m_target_x][m_target_y] * (m_target_x-1);
        swap(m_a[m_target_x][m_target_y], m_a[m_target_x-1][m_target_y+dif_y]);
        m_actions.push_back(Action(m_target_x, m_target_y, m_target_x-1, m_target_y+dif_y));
        m_target_x--;
        m_target_y += dif_y;
        while(!is_end_state() && !can_move_left() && !can_move_right()){
            ++m_target;
            for(int i=0;i<N;i++){
                for(int j=0;j<=i;j++){
                    if(m_a[i][j] == m_target){
                        m_target_x = i;
                        m_target_y = j;
                        break;
                    }
                }
            }
        }
    }
    vector<vector<int>> m_a;
    vector<Action> m_actions;
    int m_target;
    int m_target_x;
    int m_target_y;
    int m_eval;
};

int main(){
    State state;
    state.get_input();
    priority_queue<pair<int, State>, vector<pair<int, State>>, function<bool(pair<int, State>, pair<int, State>)>> pq(
        [](const pair<int, State>& a, const pair<int, State>& b) -> bool {
            return a.first < b.first;
        }
    );
    pq.push({state.get_eval(), state});
    set<vector<vector<int>>> visited;
    visited.insert(state.get_state());
    const int beam_width = 30;
    State end_state;
    int step = 0;
    while(true){
        bool end = false;
        priority_queue<pair<int, State>, vector<pair<int, State>>, function<bool(pair<int, State>, pair<int, State>)>> next_pq(
            [](const pair<int, State>& a, const pair<int, State>& b) -> bool {
                return a.first < b.first;
            }
        );
        for(int _=0;_<beam_width;_++){
            if(pq.empty()) break;
            auto [eval, state] = pq.top();
            pq.pop();
            if(state.is_end_state()){
                end_state = state;
                end = true;
                break;
            }
            if(state.can_move_left()){
                auto next = state.swap_left();
                if(visited.count(next.get_state()) == 0){
                    visited.insert(next.get_state());
                    next_pq.push({next.get_eval(), next});
                }
            }
            if(state.can_move_right()){
                auto next = state.swap_right();
                if(visited.count(next.get_state()) == 0){
                    visited.insert(next.get_state());
                    next_pq.push({next.get_eval(), next});
                }
            }
        }
        if(end) break;
        next_pq.swap(pq);
    }
    const auto& best = end_state.get_actions();
    std::cout << best.size() << endl;
    for(auto p : best){
        auto [x1, y1, x2, y2] = p.decode();
        std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    }
}
