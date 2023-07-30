use proconio::input;

fn main() {
    input! {
        n: usize,
        mut a:  [i64;3*n]
    }
    a.sort();
    println!("{}", (0..n).map(|i| a[n + 2 * i]).sum::<i64>());
}
