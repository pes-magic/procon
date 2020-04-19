use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let mut it = buf.split_whitespace();
    let x = it.next().unwrap().parse::<u32>().unwrap();
    let y = it.next().unwrap().parse::<u32>().unwrap();
    let z = it.next().unwrap().parse::<u32>().unwrap();
    println!("{} {} {}", z, x, y);
}
