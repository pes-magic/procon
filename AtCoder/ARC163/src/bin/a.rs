use proconio::input;

fn solve() -> bool {
    input! {n: usize, s: String}
    (1..n).any(|j| &s[0..j] < &s[j..])
}

fn main() {
    input! { t: usize }
    for _ in 0..t {
        println!("{}", if solve() { "Yes" } else { "No" });
    }
}
