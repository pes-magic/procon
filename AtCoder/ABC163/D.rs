use proconio::input;

fn main() {
    input! {
        n : i64,
        k : i64,
    };
    let m = 1000000007;
    let mut res = 0;
    let mut low : i64 = 0;
    let mut high : i64 = 0;
    for i in 0..=n+1 {
        if i >= k {
            res = (res + high + m - low + 1) % m;
        }
        low += i;
        high += n - i;
    }
    println!("{}", res);
}
