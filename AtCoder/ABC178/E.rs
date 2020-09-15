fn main() {
    proconio::input! {
        n: usize,
        p: [(i64, i64); n]
    }
    let x = p.iter().map(|&(a, b)| a + b).collect::<Vec<_>>();
    let y = p.iter().map(|&(a, b)| a - b).collect::<Vec<_>>();
    let dx = x.iter().max().unwrap() - x.iter().min().unwrap();
    let dy = y.iter().max().unwrap() - y.iter().min().unwrap();
    println!("{}", dx.max(dy));
}
