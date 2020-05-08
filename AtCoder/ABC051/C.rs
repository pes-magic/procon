use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let sx = it.next().unwrap().parse::<i32>().unwrap();
    let sy = it.next().unwrap().parse::<i32>().unwrap();
    let tx = it.next().unwrap().parse::<i32>().unwrap();
    let ty = it.next().unwrap().parse::<i32>().unwrap();
    let dx = (tx - sx) as usize;
    let dy = (ty - sy) as usize;
    for _ in 0..dx { print!("R") }
    for _ in 0..dy { print!("U") }
    for _ in 0..dx { print!("L") }
    for _ in 0..dy+1 { print!("D") }
    for _ in 0..dx+1 { print!("R") }
    for _ in 0..dy+1 { print!("U") }
    print!("LU");
    for _ in 0..dx+1 { print!("L") }
    for _ in 0..dy+1 { print!("D") }
    println!("R");
}
