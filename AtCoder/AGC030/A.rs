use std::io::Read;

fn main(){
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let a = it.next().unwrap().parse::<i32>().unwrap();
    let b = it.next().unwrap().parse::<i32>().unwrap();
    let c = it.next().unwrap().parse::<i32>().unwrap();
    println!("{}", b + std::cmp::min(a+b+1, c));
}