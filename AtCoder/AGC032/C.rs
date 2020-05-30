use std::io::Read;

fn solve(g: &Vec<Vec<usize>>) -> bool {
    for v in g {
        if v.len()%2 == 1 { return false }
    }
    let mut p4 = Vec::new();
    for i in 0..g.len() {
        if g[i].len() >= 6 { return true }
        if g[i].len() == 4 { p4.push(i); }
    }
    if p4.len() != 2 { return p4.len() >= 3 }
    for &t in &g[p4[0]] {
        let mut prev = p4[0];
        let mut p = t;
        while g[p].len() == 2 {
            let next = g[p][if g[p][0] != prev { 0 } else { 1 }];
            prev = p;
            p = next;
        }
        if p == p4[0] { return true }
    }
    false
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let mut g = vec![Vec::new(); n];
    for _ in 0..m {
        let a = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = it.next().unwrap().parse::<usize>().unwrap() - 1;
        g[a].push(b);
        g[b].push(a);
    }
    println!("{}", if solve(&g) { "Yes" } else { "No" });
}
