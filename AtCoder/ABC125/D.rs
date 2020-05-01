use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let a : Vec<i64> = (0..n).map(|_| it.next().unwrap().parse::<i64>().unwrap()).collect();
    let mut sum = a.iter().fold(0, |sum, t| sum + t.abs());
    if a.iter().filter(|&&x| x < 0).collect::<Vec<_>>().len() % 2 == 1 {
        sum -= 2 * a.iter().map(|x| x.abs()).min().unwrap();
    }
    println!("{}", sum);
}
