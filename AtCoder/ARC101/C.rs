use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let k = it.next().unwrap().parse::<usize>().unwrap();
    let x = (0..n).map(|_| it.next().unwrap().parse::<i32>().unwrap()).collect::<Vec<_>>();
    let mut res = 1_000_000_000;
    for i in 0..n-k+1 {
        if x[i+k-1] < 0 {
            res = std::cmp::min(res, -x[i]);
        } else if x[i] > 0 {
            res = std::cmp::min(res, x[i+k-1]);
        } else {
            res = std::cmp::min(res, 2*x[i+k-1]-x[i]);
            res = std::cmp::min(res, x[i+k-1]-2*x[i]);
        }
    }
    println!("{}", res);
}
