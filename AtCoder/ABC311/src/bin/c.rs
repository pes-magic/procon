use itertools::Itertools;
use proconio::input;
use proconio::marker::Usize1;

fn main() {
    input! {
        n: usize,
        a: [Usize1; n]
    }
    let mut mark = vec![false; n];
    let mut pos = 0;
    while !mark[pos] {
        mark[pos] = true;
        pos = a[pos];
    }
    let start = pos;
    let mut res = Vec::new();
    res.push(start + 1);
    pos = a[pos];
    while pos != start {
        res.push(pos + 1);
        pos = a[pos];
    }
    println!("{}", res.len());
    println!("{}", res.iter().join(" "));
}
