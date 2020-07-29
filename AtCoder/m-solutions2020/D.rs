fn main() {
    proconio::input! {
        n: usize,
        a: [i64; n]
    };
    let mut money = 1000;
    let mut stock = 0;
    for i in 0..n {
        if i+1 < n && a[i] < a[i+1] {
            stock += money/a[i];
            money %= a[i];
        } else if i == n-1 || a[i] > a[i+1] {
            money += a[i] * stock;
            stock = 0;
        }
    }
    println!("{}", money);
}
