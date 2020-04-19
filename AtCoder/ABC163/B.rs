use proconio::input;

fn main() {
    input! {
        n: i32,
        m: usize,
        a: [i32; m]
    };
    println!("{}", std::cmp::max(-1, n-a.iter().sum::<i32>()));
}
