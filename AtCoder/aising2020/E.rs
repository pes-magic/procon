use proconio::input;
use std::cmp::Reverse;
use std::collections::BinaryHeap;

fn solve(camels: &Vec<Vec<i64>>) -> i64 {
    let mut qu = BinaryHeap::<Reverse<i64>>::new();
    for i in 0..camels.len() {
        for &v in &camels[i] { qu.push(Reverse(v)) }
        while qu.len() > i+1 { qu.pop(); }
    }
    let mut res = 0;
    while !qu.is_empty() {
        let Reverse(v) = qu.pop().unwrap();
        res += v;
    }
    res
}

fn main() {
    input! {
        t: usize
    };
    for _ in 0..t {
        input! {
            n: usize,
            c: [(usize, i64, i64); n]
        };
        let mut l = vec![Vec::new(); n];
        let mut r = vec![Vec::new(); n];
        let mut res = 0;
        for &p in &c {
            res += p.1.min(p.2);
            if p.1 > p.2 {
                l[p.0-1].push(p.1 - p.2)
            } else if p.1 < p.2 && p.0 < n {
                r[n-p.0-1].push(p.2 - p.1)
            }
        }
        res += solve(&l);
        res += solve(&r);
        println!("{}", res);
    }
}
