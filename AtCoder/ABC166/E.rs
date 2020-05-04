use proconio::input;

fn main() {
    input! {
        n : usize,
        a : [usize; n]
    };
    let mut cnt = vec![0; n];
    let mut res : u64 = 0;
    for i in (0..n).rev() {
        let idx = a[i] + i;
        if idx < n { res += cnt[idx]; }
        if i >= a[i] { cnt[i - a[i]] += 1; }
    }
    println!("{}", res);
}
