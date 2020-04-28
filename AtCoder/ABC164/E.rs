use proconio::input;
use std::cmp::min;
use std::cmp::Reverse;
use std::collections::BinaryHeap;

fn main(){
    input! {
        n : usize,
        m : usize,
        s : usize
    };
    let max_s = 50 * n;
    let mut dist = vec![vec![1i64 << 60; max_s + 1]; n];
    let mut g : Vec<Vec<(usize, usize, i64)>> = vec![Vec::new(); n];
    for _ in 0..m {
        input! {
            u : usize,
            v : usize,
            a : usize,
            b : i64
        }
        g[u-1].push((v-1, a, b));
        g[v-1].push((u-1, a, b));
    }
    input! {
        c : [(usize, i64); n]
    };
    let mut res = vec![1i64 << 60; n];
    let mut qu = BinaryHeap::<Reverse<(i64, usize, usize)>>::new();
    qu.push(Reverse((0, 0, min(max_s, s))));
    dist[0][min(max_s, s)] = 0;
    while !qu.is_empty() {
        let Reverse((cur_cost, cur_pos, cur_s)) = qu.pop().unwrap();
        res[cur_pos] = min(res[cur_pos], cur_cost);
        let charge_s = min(max_s, cur_s + c[cur_pos].0);
        if cur_cost + c[cur_pos].1 < dist[cur_pos][charge_s] {
            dist[cur_pos][charge_s] = cur_cost + c[cur_pos].1;
            qu.push(Reverse((dist[cur_pos][charge_s], cur_pos, charge_s)));
        }
        for &(next_pos, next_s, next_cost) in &g[cur_pos] {
            if cur_s < next_s { continue; }
            if cur_cost + next_cost < dist[next_pos][cur_s - next_s] {
                dist[next_pos][cur_s - next_s] = cur_cost + next_cost;
                qu.push(Reverse((dist[next_pos][cur_s - next_s], next_pos, cur_s - next_s)));
            }
        }
    }
    for i in 1..n { println!("{}", res[i]); }
}