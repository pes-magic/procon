use proconio::input;

fn main() {
    input!{
        n: usize,
        x: i32,
        a: [i32; n]
    };
    let m = a.iter().max().unwrap();
    println!("{}", a.iter().filter(|&&t| t >= *m - x).count());
}
