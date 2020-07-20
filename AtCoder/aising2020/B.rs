use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [usize; n]
    };
    println!("{}", a.iter().step_by(2).fold(0, |x, y| x + y%2));
}
