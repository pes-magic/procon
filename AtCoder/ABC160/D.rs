use std::io::Read;
use std::collections::BinaryHeap;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let x = it.next().unwrap().parse::<usize>().unwrap() - 1;
    let y = it.next().unwrap().parse::<usize>().unwrap() - 1;
    let mut res = vec![0; n];
    for s in 0..n {
        let mut d : Vec<i32> = vec![10000; n];
        d[s] = 0;
        let mut qu = BinaryHeap::new();
        qu.push((0i32, s));
        while !qu.is_empty() {
            let (_, pos) = qu.pop().unwrap();
            let mut update = |p : usize| {
                if d[p] > d[pos] + 1 {
                    d[p] = d[pos] + 1;
                    qu.push((-d[p], p));
                }
            };
            if pos > 0 { update(pos - 1) }
            if pos + 1 < n { update(pos + 1) }
            if pos == x { update(y) }
            if pos == y { update(x) }
        }
        for i in s+1..n { res[d[i] as usize] += 1 }
    }
    for i in 1..n { println!("{}", res[i]) }
}
