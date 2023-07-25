use proconio::input;

fn main() {
    input! {
        n:usize, m:usize,
        l:i32, h:i32, mut a: [i32;n-2]
    }
    a.sort();
    let mut res = 2000000000;
    for i in 0..=n - 2 - m {
        res = res.min((l - a[i]).max(0) + (a[i + m - 1] - h).max(0));
    }
    println!("{}", res);
}
