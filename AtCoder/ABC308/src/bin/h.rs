use proconio::input;
use std::cmp::Reverse;
use std::collections::BinaryHeap;

const INF: i32 = 1000000000;

fn solve(
    edge: &Vec<(usize, usize, i32)>,
    g: &Vec<Vec<(i32, usize)>>,
    src: usize,
    stop: usize,
) -> i32 {
    let mut dist = vec![INF; g.len()];
    let mut label = vec![!0; g.len()];
    let mut qu: BinaryHeap<Reverse<(i32, usize)>> = BinaryHeap::new();
    qu.push(Reverse((0, src)));
    dist[src] = 0;
    label[src] = src;
    let mut res = INF;
    while let Some(Reverse((d, pos))) = qu.pop() {
        for &e in &g[pos] {
            if pos == src && e.1 == stop {
                continue;
            }
            let nd = d + e.0;
            let np = e.1;
            if dist[np] > nd {
                dist[np] = nd;
                label[np] = if pos == src { np } else { label[pos] };
                qu.push(Reverse((nd, np)));
            }
        }
    }
    let mut v0 = 0;
    let mut v1 = 0;
    for &e in edge {
        let e0 = e.0 - 1;
        let e1 = e.1 - 1;
        if dist[e0] == INF || dist[e1] == INF {
            continue;
        }
        if label[e0] == label[e1] {
            continue;
        }
        let sum = dist[e0] + dist[e1] + e.2;
        let m0 = if label[e0] == src {
            if e0 == src {
                e1
            } else {
                e0
            }
        } else {
            label[e0]
        };
        let m1 = if label[e1] == src {
            if e0 == src {
                e1
            } else {
                e0
            }
        } else {
            label[e1]
        };
        if m0 == m1 {
            continue;
        }
        for i in 0..g[src].len() {
            if g[src][i].1 != m0 && g[src][i].1 != m1 {
                if res > sum + g[src][i].0 {
                    res = sum + g[src][i].0;
                    v0 = m0;
                    v1 = m1;
                }
                break;
            }
        }
    }
    if res < INF && stop == !0 {
        res = res.min(solve(edge, g, src, v0));
        res = res.min(solve(edge, g, src, v1));
    }
    res
}

fn main() {
    input! {
        n:usize, m:usize,
        edge:[(usize, usize, i32);m]
    }
    let mut g = vec![Vec::new(); n];
    for &e in &edge {
        g[e.0 - 1].push((e.2, e.1 - 1));
        g[e.1 - 1].push((e.2, e.0 - 1));
    }
    for i in 0..n {
        g[i].sort();
    }
    let mut res = INF;
    for i in 0..n {
        res = res.min(solve(&edge, &g, i, !0))
    }
    println!("{}", if res < INF { res } else { -1 });
}
