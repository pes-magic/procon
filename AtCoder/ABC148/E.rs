use std::io::Read;

fn calc_sum(n : i64, m : i64) -> i64 {
    let mut res = 0;
    let mut val = n;
    while val >= m {
        res += val / m;
        val /= m;
    }
    res
}

fn solve(n : i64) -> i64 {
    if n%2 == 0 {
        std::cmp::min(calc_sum(n, 2), calc_sum(n/2, 5))
    } else {
        0
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let n = buf.trim_right().parse::<i64>().unwrap();
    println!("{}", solve(n));
}
