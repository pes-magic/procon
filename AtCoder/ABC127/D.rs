use std::collections::BinaryHeap;
use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut iter = buf.split_whitespace();
    let n = iter.next().unwrap().parse::<usize>().unwrap();
    let m = iter.next().unwrap().parse::<usize>().unwrap();
    let mut h = BinaryHeap::new();
    for _i in 0..n {
        h.push((iter.next().unwrap().parse::<i64>().unwrap(), 1));
    }
    for _i in 0..m {
        let b = iter.next().unwrap().parse::<i64>().unwrap();
        let c = iter.next().unwrap().parse::<i64>().unwrap();
        h.push((c, b));
    }
    let mut res = 0;
    let mut rest = n as i64;
    for _i in 0..n {
        let (b, c) = h.pop().unwrap();
        res += std::cmp::min(rest, c) * b;
        rest = std::cmp::max(0, rest - c);
    }
    println!("{}", res);
}
