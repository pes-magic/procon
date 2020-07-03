use proconio::input;

fn solve(m: i64, k: i64) -> i64 {
    let mut res = 1;
    let mut sum = 0;
    loop {
        sum += k * (2 * sum + 1);
        if sum >= m { return res }
        res += 1;
    }
}

fn main() {
    input! {
        m : i64,
        k : i64
    };
    println!("{}", solve(m, k));
}
