use std::collections::VecDeque;

fn dist(g : &Vec<Vec<usize>>, start : usize) -> Vec<i32> {
    let mut res = vec![-1; g.len()];
    res[start] = 0;
    let mut qu = VecDeque::new(); qu.push_back(start);
    while !qu.is_empty() {
        let p = qu.pop_front().unwrap();
        for &t in &g[p] {
            if res[t] != -1 { continue }
            res[t] = res[p] + 1;
            qu.push_back(t);
        }
    }
    res
}

fn main() {
    proconio::input! {
        n : usize,
        e : [(proconio::marker::Usize1, proconio::marker::Usize1); n-1]
    }
    let mut g = vec![Vec::new(); n];
    for &p in &e {
        g[p.0].push(p.1);
        g[p.1].push(p.0);
    }
    let a = dist(&g, 0);
    let b = dist(&g, n-1);
    let mut cnt = 0;
    for i in 0..n {
        if a[i] <= b[i] { cnt += 1 }
    }
    println!("{}", if cnt > n-cnt { "Fennec" } else { "Snuke" });
}
