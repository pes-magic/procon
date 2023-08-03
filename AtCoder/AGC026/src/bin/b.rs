use proconio::input;

fn gcd(a: i64, b: i64) -> i64 {
    return if a % b == 0 { b } else { gcd(b, a % b) };
}

fn check(a: i64, b: i64, c: i64, d: i64) -> bool {
    if a < b {
        return false;
    }
    if d < b {
        return false;
    }
    if c >= b - 1 {
        return true;
    }
    let s = a % b;
    if s > c {
        return false;
    }
    if d % b == 0 {
        return true;
    }
    let m = gcd(b, d);
    b - m + s % m <= c
}

fn main() {
    input! {
        t: usize,
        q: [(i64, i64, i64, i64); t]
    }
    for &(a, b, c, d) in &q {
        println!("{}", if check(a, b, c, d) { "Yes" } else { "No" });
    }
}
