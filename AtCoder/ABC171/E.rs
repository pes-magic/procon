use proconio::input;

fn main() {
    input! {
        n : usize,
        a : [u32; n]
    };
    let x = a.iter().fold(0, |s, t| s ^ t);
    for &t in &a { print!("{} ", x^t) }
    println!("");
}
