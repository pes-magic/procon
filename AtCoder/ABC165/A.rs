use proconio::input;

fn main() {
    input! {
        (k, a, b) : (u64, u64, u64)
    }
    println!("{}", if (a+k-1)/k <= b/k { "OK" } else { "NG" });
}
