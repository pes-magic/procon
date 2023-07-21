use proconio::input;

fn main() {
    input! {
        t:usize,
        c:[(u64,u64);t]
    }
    for &(n, k) in &c {
        if n % 2 != k % 2 {
            println!("No");
            continue;
        }
        let mut v = n;
        let mut s = 0;
        while v > 0 {
            s += v % 3;
            v /= 3;
        }
        println!("{}", if s <= k { "Yes" } else { "No" });
    }
}
