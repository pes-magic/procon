use proconio::input;

fn main() {
    input! {
        s: String
    }
    println!("{}", if s.chars().any(|c| c == '7') { "Yes" } else { "No" });
}
