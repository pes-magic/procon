use std::io::Read;

fn solve(a: &Vec<i64>) -> i64 {
    let n = a.len();
    if a[0] != 0 { return -1; }
    let mut res = 0;
    let mut ex = 0;
    for i in 0..n {
        if a[n-1-i] < ex { return -1; }
        if a[n-1-i] > ex {
            res += a[n-1-i];
            ex = a[n-1-i];
        }
        ex = std::cmp::max(0, ex-1);
    }
    return res;
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<i64>().unwrap()).collect::<Vec<_>>();
    println!("{}", solve(&a));
}
