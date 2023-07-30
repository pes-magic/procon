use itertools::Itertools;
use proconio::input;
use proconio::marker::Usize1;
use std::collections::VecDeque;

fn main() {
    input! {
        n: usize, m: usize,
        edges: [(Usize1, Usize1); m]
    }
    let mut res = VecDeque::new();
    let mut visited = vec![false; n];
    res.push_back(edges[0].0);
    res.push_back(edges[0].1);
    visited[edges[0].0] = true;
    visited[edges[0].1] = true;
    let mut g = vec![Vec::new(); n];
    for &e in &edges {
        g[e.0].push(e.1);
        g[e.1].push(e.0);
    }
    loop {
        let pos = res.front().unwrap();
        let mut cont = false;
        for &p in &g[*pos] {
            if !visited[p] {
                res.push_front(p);
                visited[p] = true;
                cont = true;
                break;
            }
        }
        if !cont {
            break;
        }
    }
    loop {
        let pos = res.back().unwrap();
        let mut cont = false;
        for &p in &g[*pos] {
            if !visited[p] {
                res.push_back(p);
                visited[p] = true;
                cont = true;
                break;
            }
        }
        if !cont {
            break;
        }
    }
    println!("{}", res.len());
    println!("{}", res.iter().map(|p| p + 1).join(" "));
}
