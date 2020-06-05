use std::io::Read;

fn solve(g: &Vec<Vec<usize>>, s1: usize, s2: usize) -> (i64, i64) {
    let mut color = vec![-1; g.len()];
    let mut res = 1;
    color[s1] = 1;
    if s2 != !0 { color[s2] = 1; res += 1; }
    let mut cur = 1;
    loop {
        let mut mx = 0;
        for i in 0..g.len() {
            if color[i] != cur { continue }
            let mut cnt = 0;
            for &t in &g[i] {
                if color[t] != -1 { continue; }
                cnt += 1;
                color[t] = cur + 1;
            }
            mx = std::cmp::max(mx, cnt);
        }
        if mx == 0 { break }
        res *= mx;
        if res >= 1 << 60 { return (100000, 1 << 60) }
        cur += 1;
    }
    (cur, res)
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
    let mut res = (100000, 0);
    for i in 0..n {
        res = std::cmp::min(res, solve(&g, i, !0));
        for &t in &g[i] {
            if t < i {
                res = std::cmp::min(res, solve(&g, i, t));
            }
        }
    }
    println!("{} {}", res.0, res.1);
}
