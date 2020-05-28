use std::io::Read;

fn search(g : &Vec<Vec<usize>>, s: &[u8], pos : usize, prev : usize) -> (i32, i32, i32) {
    let mut res = (0, 0, 0);
    let mut child_res = Vec::new();
    for &t in &g[pos] {
        if t == prev { continue }
        let r = search(g, s, t, pos);
        res.0 += r.0;
        res.2 += r.0 + r.2;
        child_res.push((r.1 + r.0, r.2 + r.0));
    }
    res.1 = res.2 % 2;
    for p in child_res {
        res.1 = std::cmp::max(res.1, p.0 - (res.2 - p.1));
    }
    if s[pos] == b'1' { res.0 += 1 }
    res
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let s = it.next().unwrap().as_bytes();
    let mut g = vec![Vec::new(); n];
    for _ in 0..n-1 {
        let a = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = it.next().unwrap().parse::<usize>().unwrap() - 1;
        g[a].push(b);
        g[b].push(a);
    }
    let mut res = None;
    for i in 0..n {
        let r = search(&g, s, i, n);
        if r.1 == 0 {
            if let Some(p) = res {
                res = Some(std::cmp::min(p, r.2/2));
            } else {
                res = Some(r.2/2);
            }
        }
    }
    println!("{}", res.unwrap_or(-1));
}
