use std::collections::VecDeque;

fn main() {
    proconio::input! {
        n: usize,
        edge: [(proconio::marker::Usize1, proconio::marker::Usize1); n-1],
        mut c: [i64; n]
    }
    c.sort();
    println!("{}", c[0..n-1].iter().sum::<i64>());
    let mut g = vec![Vec::new(); n];
    let mut deg = vec![0; n];
    for &e in &edge {
        g[e.0].push(e.1);
        g[e.1].push(e.0);
    }
    let mut qu = VecDeque::new();
    for i in 0..n {
        deg[i] = g[i].len();
        if deg[i] == 1 { qu.push_back(i) }
    }
    let mut res = vec![0; n];
    let mut idx = 0;
    while !qu.is_empty() {
        let p = qu.pop_front().unwrap();
        res[p] = c[idx];
        idx += 1;
        for &nxt in &g[p] {
            deg[nxt] -= 1;
            if deg[nxt] == 1 { qu.push_back(nxt) }
        }
    }
    print!("{}", res[0]);
    for i in 1..n { print!(" {}", res[i]) }
    println!("");
}
