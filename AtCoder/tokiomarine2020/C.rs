use proconio::input;
use std::cmp::{min, max};

fn main() {
    input! {
        n : usize,
        k : usize,
        a : [i64; n]
    };
    let mut end = k;
    let mut res = vec![vec![0; n]; 2];
    let mut add : Vec<i64> = vec![0; n+1];
    for i in 0..n { res[0][i] = a[i]; }
    for i in 0..k {
        for j in 0..=n { add[j] = 0 }
        for j in 0..n {
            add[max(0, j as i64 - res[i%2][j]) as usize] += 1;
            add[min(n as i64, j as i64 + 1 + res[i%2][j]) as usize] -= 1;
        }
        res[1-i%2][0] = add[0];
        for j in 1..n {
            res[1-i%2][j] = res[1-i%2][j-1] + add[j];
        }
        let mut ok = true;
        for j in 0..n {
            if res[1-i%2][j] != n as i64 { ok = false; }
        }
        if ok {
            end = i+1;
            break;
        }
    }
    for i in 0..n { print!("{} ", res[end%2][i]) }
    println!("");
}
