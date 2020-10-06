fn main() {
    proconio::input!{
        n: i64
    }
    let m = n%9;
    println!("{}", if m == 8 || m%2 == 1 { "Win" } else { "Lose" });
}
