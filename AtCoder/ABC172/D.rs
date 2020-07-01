use proconio::input;

fn main() {
    input! {
        n: i64
    };
    let mut res = 0;
    for i in 1..=n {
        let up = n/i;
        res += i * up * (up+1) / 2;
    }
    println!("{}", res);
}

