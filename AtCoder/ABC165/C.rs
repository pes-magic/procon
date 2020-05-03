use proconio::input;
use itertools::Itertools;

fn main() {
    input! {
        (n, m, q) : (usize, usize, usize),
        cond : [(usize, usize, usize, u64); q]
    }
    let mut res = 0;
    for v in (0..m).combinations_with_replacement(n) {
        let mut score = 0;
        for &c in &cond {
            if v[c.1-1] - v[c.0-1] == c.2 { score += c.3; }
        }
        res = std::cmp::max(res, score);
    }
    println!("{}", res);
}
