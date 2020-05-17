use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let k = it.next().unwrap().parse::<i32>().unwrap();
    let t = it.next().unwrap().parse::<usize>().unwrap();
    let m = (0..t).map(|_| it.next().unwrap().parse::<i32>().unwrap()).max().unwrap();
    println!("{}", std::cmp::max(0, m-(k-m)-1));
}
