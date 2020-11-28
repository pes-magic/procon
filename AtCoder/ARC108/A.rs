fn check(s : i64, p : i64) -> bool {
    for i in 1..=p {
        if i*i > p { return false }
        if p%i != 0 { continue }
        let b = p/i;
        if i+b == s { return true }
    }
    false
}

fn main() {
    proconio::input! {
        s : i64,
        p : i64
    }
    println!("{}", if check(s, p) { "Yes" } else { "No" });
}
