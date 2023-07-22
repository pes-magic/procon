use proconio::input;
use proconio::marker::Usize1;
use std::collections::VecDeque;

fn main() {
    input! {
        n: usize, m: usize,
        edges: [(Usize1, Usize1); m],
        c: [usize;n]
    }
    let mut root = vec![n; n];
    let mut g = vec![Vec::new(); n];
    for e in edges {
        g[e.0].push(e.1);
        g[e.1].push(e.0);
    }
    let mut ok = false;
    for i in 0..n {
        if root[i] != n {
            continue;
        }
        let mut qu = VecDeque::new();
        qu.push_back(i);
        root[i] = i;
        while let Some(pos) = qu.pop_front() {
            for &np in &g[pos] {
                if root[np] == n && c[np] != c[pos] {
                    root[np] = i;
                    qu.push_back(np);
                } else if root[np] == i && c[np] == c[pos] {
                    ok = true;
                }
            }
        }
    }
    println!("{}", if ok { "Yes" } else { "No" });
}
