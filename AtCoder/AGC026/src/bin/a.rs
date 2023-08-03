use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [usize; n]
    }
    let mut prev = 0;
    let mut cnt = 0;
    let mut res = 0;
    for &c in &a {
        if c == prev {
            cnt += 1;
            res += cnt % 2;
        } else {
            cnt = 0;
            prev = c;
        }
    }
    println!("{}", res);
}
