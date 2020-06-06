use std::io::Read;
use std::collections::VecDeque;

const MOD: i64 = 1_000_000_007;
const INV2: i64 = MOD - MOD/2;

fn solve(g: &Vec<Vec<usize>>, pos: usize) -> VecDeque<(i64, i64)> {
    if g[pos].is_empty() {
        return VecDeque::from(vec![(INV2, INV2)]);
    }
    let mut update_idx = 0;
    let mut res = solve(g, g[pos][0]);
    for i in 1..g[pos].len() {
        let mut cur = solve(&g, g[pos][i]);
        if res.len() < cur.len() {
            update_idx = std::cmp::max(update_idx, res.len());
            for j in 0..res.len() {
                cur[j].1 = (cur[j].0 * res[j].1 + cur[j].1 * res[j].0) % MOD;
                cur[j].0 = cur[j].0 * res[j].0 % MOD;
            }
            res = cur;
        } else {
            update_idx = std::cmp::max(update_idx, cur.len());
            for j in 0..cur.len() {
                res[j].1 = (res[j].0 * cur[j].1 + res[j].1 * cur[j].0) % MOD;
                res[j].0 = res[j].0 * cur[j].0 % MOD;
            }
        }
    }
    for i in 0..update_idx { res[i].0 =  (1 + MOD - res[i].1) % MOD }
    res.push_front((INV2, INV2));
    return res;
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap() + 1;
    let mut g = vec![Vec::new(); n];
    for i in 1..n {
        let p = it.next().unwrap().parse::<usize>().unwrap();
        g[p].push(i);
    }
    let all = solve(&g, 0);
    let mut res = 0;
    for &t in &all { res = (res + t.1) % MOD }
    for _ in 0..n { res = 2 * res % MOD }
    println!("{}", res);
}
