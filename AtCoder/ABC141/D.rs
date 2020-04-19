use std::collections::BinaryHeap;
use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<i64>().unwrap()).collect::<Vec<_>>();
    let mut qu = BinaryHeap::from(a);
    for _i in 0..m {
        let v = qu.pop().unwrap();
        qu.push(v/2);
    }
    println!("{}", qu.iter().sum::<i64>());
}
