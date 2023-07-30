use itertools::Itertools;
use proconio::input;
use proconio::marker::Usize1;
use std::collections::VecDeque;

fn solve(g: &Vec<Vec<usize>>, a: &Vec<i32>) -> bool {
    let n = g.len();
    let mut deg = (0..n).map(|i| g[i].len()).collect_vec();
    let mut rest = vec![0; n];
    let mut qu = VecDeque::new();
    for i in 0..n {
        rest[i] = a[i];
        if deg[i] == 1 {
            qu.push_front(i);
        } else {
            rest[i] *= 2;
        }
    }
    let mut visit = vec![false; n];
    while let Some(p) = qu.pop_front() {
        if rest[p] > a[p] {
            return false;
        }
        visit[p] = true;
        for &t in &g[p] {
            if visit[t] {
                continue;
            }
            if a[t] < rest[p] || rest[t] < rest[p] {
                return false;
            }
            rest[t] -= rest[p];
            rest[p] = 0;
            deg[t] -= 1;
            if deg[t] == 1 {
                qu.push_back(t);
            }
        }
    }
    rest.iter().all(|r| *r == 0)
}

fn main() {
    input! {
        n: usize, a: [i32; n], edges: [(Usize1, Usize1); n-1]
    }
    let mut g = vec![Vec::new(); n];
    for &e in &edges {
        g[e.0].push(e.1);
        g[e.1].push(e.0);
    }
    println!("{}", if solve(&g, &a) { "YES" } else { "NO" });
}
