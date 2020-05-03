use proconio::input;

fn main() {
    input! {
        (a, b, n) : (u64, u64, u64)
    };
    let x  = n.min(b-1);
    println!("{}", a*x/b);
}
