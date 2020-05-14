use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<i32>().unwrap()).collect::<Vec<_>>();
    let b = a.iter().max().unwrap();
    let c = a.iter().max_by_key(|&&x| (std::cmp::min(x, b-x), -x)).unwrap();
    println!("{} {}", b, c);
}
