use std::io::Read;

fn digit_sum(v: i32) -> i32 {
    let mut val = v;
    let mut res = 0;
    while val > 0 {
        res += val % 10;
        val /= 10;
    }
    res
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let n = buf.trim().parse::<i32>().unwrap();
    let mut res = 10000000;
    for i in 1..n {
        res = std::cmp::min(res, digit_sum(i) + digit_sum(n-i));
    }
    println!("{}", res);
}
