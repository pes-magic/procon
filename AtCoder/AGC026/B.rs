use std::io::Read;

fn gcd(a : i64, b: i64) -> i64 {
    return if a%b == 0 { b } else { gcd(b, a%b) }
}

fn check(a: i64, b: i64, c: i64, d: i64) -> bool {
    if a < b { return false }
    if d < b { return false }
    if c >= b - 1 { return true }
    let s = a % b;
    if s > c { return false }
    if d%b == 0 { return true }
    let m = gcd(b, d);
    b - m + s%m <= c
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let t = it.next().unwrap().parse::<usize>().unwrap();
    for _ in 0..t {
        let a = it.next().unwrap().parse::<i64>().unwrap();
        let b = it.next().unwrap().parse::<i64>().unwrap();
        let c = it.next().unwrap().parse::<i64>().unwrap();
        let d = it.next().unwrap().parse::<i64>().unwrap();
        println!("{}", if check(a, b, c, d) { "Yes" } else { "No" });
    }
}
