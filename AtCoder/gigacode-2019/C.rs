fn main() {
    proconio::input! {
        d: usize,
        a: [i64; d],
        b: [i64; d]
    }
    let mut res = -1;
    let mut sum = 0;
    for i in 0..d {
        sum += a[i];
        if b[i] <= sum && (res == -1 || b[i] < res) { res = b[i] }
    }
    println!("{}", res);
}
