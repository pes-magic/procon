use proconio::input;
use std::collections::{BTreeMap, BTreeSet};

fn main() {
    input! {
        n:usize, m:usize,
        p:[i64;n],
        l:[i64;m],
        d:[i64;m]
    }
    let mut rest = BTreeSet::new();
    let mut cnt = BTreeMap::new();
    for v in &p {
        rest.insert(*v);
        *cnt.entry(*v).or_insert(0) += 1;
    }
    let mut ticket: Vec<(i64, i64)> = l.iter().zip(d.iter()).map(|(&x, &y)| (x, y)).collect();
    ticket.sort_by_key(|&(_, b)| std::cmp::Reverse(b));
    let mut res: i64 = p.iter().sum();
    for t in &ticket {
        if let Some(v) = rest.range(t.0..).next().cloned() {
            res -= t.1;
            *cnt.entry(v).or_insert(0) -= 1;
            if cnt[&v] == 0 {
                rest.remove(&v);
            }
        }
    }
    println!("{}", res);
}
