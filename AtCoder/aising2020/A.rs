fn main() {
    proconio::input! {
        l: usize,
        r: usize,
        d: usize
    }
    println!("{}", (l..=r).into_iter().filter(|x| x%d==0).count());
}
