use std::io::Read;
use std::collections::VecDeque;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let s = it.next().unwrap().as_bytes();
    let mut to = vec![vec![0; n]; 2];
    let mut g = vec![Vec::new(); n];
    for _ in 0..m {
        let a = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = it.next().unwrap().parse::<usize>().unwrap() - 1;
        to[(s[b]-b'A') as usize][a] += 1;
        to[(s[a]-b'A') as usize][b] += 1;
        g[a].push(b);
        g[b].push(a);
    }
    let mut visit = vec![0; n];
    let mut qu = VecDeque::new();
    for i in 0..n {
        if to[0][i] == 0 || to[1][i] == 0 {
            qu.push_back(i);
            visit[i] = 1;
        }
    }
    while !qu.is_empty() {
        let p = qu.pop_front().unwrap();
        let idx = (s[p] - b'A') as usize;
        for &t in &g[p] {
            to[idx][t] -= 1;
            if to[idx][t] == 0 && visit[t] == 0 {
                qu.push_back(t);
                visit[t] = 1;
            }
        }
    }
    println!("{}", if visit.iter().any(|&x| x == 0) { "Yes" } else { "No" });
}
