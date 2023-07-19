use proconio::input;
use std::collections::HashMap;

fn main() {
    input! {
        n: usize,
        m:usize,
        c: [String; n],
        d: [String; m],
        p: [u32; m+1]
    }
    let mut price = HashMap::new();
    for i in 0..m {
        price.insert(d[i].as_str(), p[i + 1]);
    }
    let res: u32 = c
        .iter()
        .map(|c| price.get(c.as_str()).unwrap_or(&p[0]))
        .sum();
    println!("{}", res);
}
