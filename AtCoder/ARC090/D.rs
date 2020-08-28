use std::collections::VecDeque;

fn main() {
    proconio::input! {
        n: usize,
        m: usize,
        d: [(proconio::marker::Usize1, proconio::marker::Usize1, i64); m]
    };
    let mut g = vec![Vec::new(); n];
    for &p in &d {
        g[p.0].push((p.1, p.2));
        g[p.1].push((p.0, -p.2));
    }
    let mut visit = vec![0; n];
    let mut pos = vec![0; n];
    let mut valid = true;
    for i in 0..n {
        if visit[i] == 1 { continue }
        visit[i] = 1;
        let mut qu = VecDeque::new(); qu.push_back(i);
        while let Some(p) = qu.pop_front() {
            for &e in &g[p] {
                if visit[e.0] == 1 {
                    if pos[e.0] - pos[p] != e.1 {
                        valid = false;
                    }
                } else {
                    pos[e.0] = pos[p] + e.1;
                    visit[e.0] = 1;
                    qu.push_front(e.0);
                }
            }
        };
    }
    println!("{}", if valid { "Yes" } else { "No" });
}
