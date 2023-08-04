fn main() {
    proconio::input! {x:i64, y:i64}
    if x % y == 0 {
        println!("-1");
    } else {
        println!("{}", x);
    }
}
