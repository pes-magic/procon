use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i64; n],
        b: [i64; n]
    }
    let s = (0..n).map(|i| (a[i] - b[i]).max(0)).sum::<i64>();
    let p = (0..n).map(|i| (b[i] - a[i]).max(0) / 2).sum::<i64>();
    if p >= s {
        println!("Yes");
    } else {
        println!("No");
    }
}
