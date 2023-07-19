use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n: usize,
        coin: [(usize, usize); n]
    }
    let mut res = (0..n).collect::<Vec<usize>>();
    res.sort_by(|a, b| {
        (coin[*b].0 * (coin[*a].0 + coin[*a].1), *a)
            .cmp(&(coin[*a].0 * (coin[*b].0 + coin[*b].1), *b))
    });
    println!("{}", res.iter().map(|&m| m + 1).join(" "));
}
