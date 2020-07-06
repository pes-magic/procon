use proconio::input;

fn main() {
    input!{
        n: i64
    };
    let mut res = n * (n+1) * (n+2) / 6;
    for _ in 1..n {
        input! {
            a: i64,
            b: i64
        };
        res -= std::cmp::min(a, b) * (n - std::cmp::max(a, b) + 1);
    }
    println!("{}", res);
}
