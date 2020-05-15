use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut a = Vec::new();
    for _ in 0..n {
        let x = it.next().unwrap().parse::<i32>().unwrap();
        let l = it.next().unwrap().parse::<i32>().unwrap();
        a.push((x-l, x+l));
    }
    a.sort_by_key(|x| x.1);
    let mut last = -(1<<30);
    let mut res = 0;
    for &p in &a {
        if last <= p.0 {
            last = p.1;
            res += 1;
        }
    }
    println!("{}", res);
}
