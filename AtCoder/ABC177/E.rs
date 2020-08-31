fn solve(a: Vec<i64>) -> &'static str {
    if a.iter().fold(a[0], |x, &y| num::integer::gcd(x, y)) > 1 {
        return "not coprime"
    }
    let mut m = vec![0; 1000000];
    for &t in &a {
        let mut v = t as usize;
        for div in 2..v {
            if div*div > v { break }
            if v%div != 0 { continue }
            if m[div] != 0 { return "setwise coprime" }
            while v%div == 0 { v /= div }
            m[div] = 1
        }
        if v > 1 {
            if m[v] != 0 { return "setwise coprime" }
            m[v] = 1
        }
    }
    "pairwise coprime"
}

fn main() {
    proconio::input! {
        n: usize,
        a: [i64; n]
    }
    println!("{}", solve(a));
}
