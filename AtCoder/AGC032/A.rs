use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut b = (0..n).map(|_| it.next().unwrap().parse::<usize>().unwrap()).collect::<Vec<_>>();
    let mut res = Vec::new();
    for _ in 0..n {
        let mut idx = !0;
        for j in 0..b.len() {
            if b[j] == j+1 { idx = j }
        }
        if idx == !0 { break }
        res.push(idx+1);
        b.remove(idx);
    }
    if b.is_empty() {
        res.reverse();
        for &r in &res {
            println!("{}", r);
        }
    } else {
        println!("-1");
    }
}
