use proconio::input;

fn main() {
    input! {
        n : i64
    }
    println!("{}", (1..=n).filter(|&x| x % 3 != 0 && x % 5 != 0).sum::<i64>());
}
