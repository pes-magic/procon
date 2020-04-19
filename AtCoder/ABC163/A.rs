use proconio::input;

fn main() {
    input! {
        n : f64
    };
    println!("{:.12}", 2.0 * n * std::f64::consts::PI);
}
