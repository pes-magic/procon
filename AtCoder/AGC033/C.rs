use std::io::Read;

fn far(g: &Vec<Vec<usize>>, pos: usize, prev: usize, cur: usize) -> (usize, usize) {
    let mut res = (cur, pos);
    for &t in &g[pos] {
        if t == prev { continue }
        res = std::cmp::max(res, far(g, t, pos, cur+1));
    }
    res
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut g = vec![Vec::new(); n];
    for _ in 0..n-1 {
        let a = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = it.next().unwrap().parse::<usize>().unwrap() - 1;
        g[a].push(b);
        g[b].push(a);
    }
    let d = far(&g, far(&g, 0, !0, 1).1, !0, 1).0;
    println!("{}", if d%3 == 2 { "Second" } else { "First" });
}
