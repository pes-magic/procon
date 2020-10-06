fn main() {
    proconio::input! {
        n: usize
    }
    let mut v : i64 = 1789997546303;
    for _ in 0..1000-n {
        v = if v%2 == 1 { 3*v+1 } else { v/2 };
    }
    println!("{}", v);
}
