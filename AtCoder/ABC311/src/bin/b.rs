use proconio::input;
use proconio::marker::Chars;

fn main() {
    input! {
        n:usize, d:usize,
        s: [Chars;n]
    }
    let mut res = 0;
    let mut cur = 0;
    for i in 0..d {
        if (0..n).into_iter().all(|j| s[j][i] == 'o') {
            cur = cur + 1;
        } else {
            cur = 0;
        }
        res = res.max(cur);
    }
    println!("{}", res);
}
