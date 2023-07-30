use proconio::input;

fn solve(a: i64, b: i64) -> i64 {
    if a == b {
        return 1;
    }
    let mut p = 60;
    while ((a ^ b) & (1 << p)) == 0 {
        p -= 1;
    }
    let na = a % (1 << p);
    let nb = b % (1 << p);
    let mut q = p - 1;
    while q >= 0 && (nb & (1 << q)) == 0 {
        q -= 1;
    }
    2 * ((1 << p) - na) + na.min(1 << (q + 1))
}

fn main() {
    input! {a:i64, b:i64}
    println!("{}", solve(a, b));
}
