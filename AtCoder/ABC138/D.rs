use std::io::Read;
use std::collections::VecDeque;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let q = it.next().unwrap().parse::<usize>().unwrap();
    let mut g = vec![Vec::new(); n];
    for _ in 0..n-1 {
        let a = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = it.next().unwrap().parse::<usize>().unwrap() - 1;
        g[a].push(b);
        g[b].push(a);
    }
    let mut res = vec![0; n];
    for _ in 0..q {
        let p = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let x = it.next().unwrap().parse::<i64>().unwrap();
        res[p] += x;
    }
    let mut qu = VecDeque::new();
    qu.push_back(0);
    let mut visit = vec![0; n];
    visit[0] = 1;
    while !qu.is_empty() {
        let p = qu.pop_front().unwrap();
        for &t in &g[p] {
            if visit[t] == 1 { continue }
            visit[t] = 1;
            res[t] += res[p];
            qu.push_back(t);
        }
    }
    print!("{}", res[0]);
    for i in 1..n { print!(" {}", res[i]); }
    println!("");
}
