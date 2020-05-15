use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let s = buf.trim();
    let n = s.len();
    let mut g = vec![Vec::new(); n];
    let mut reach = vec![0; n+1];
    reach[0] = 1;
    for &t in &["dream", "dreamer", "erase", "eraser"] {
        for p in s.match_indices(t) {
            g[p.0].push(p.0 + t.len());
        }
    }
    for i in 0..n {
        if reach[i] == 0 { continue }
        for &t in &g[i] { reach[t] = 1; }
    }
    println!("{}", if reach[n] == 1 { "YES" } else { "NO" });
}
