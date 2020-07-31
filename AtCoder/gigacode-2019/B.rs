fn main() {
    proconio::input!{
        n: usize,
        x: i32,
        y: i32,
        z: i32,
        d: [(i32, i32); n]
    };
    println!("{}", d.iter().filter(|&a| a.0 >= x && a.1 >= y && a.0 + a.1 >= z).count());
}
