fn main() {
    proconio::input! {
        n: usize
    }
    for i in 1..=n {
        let mut p = false;
        if i%2 == 0 { p = true; print!("a"); }
        if i%3 == 0 { p = true; print!("b"); }
        if i%4 == 0 { p = true; print!("c"); }
        if i%5 == 0 { p = true; print!("d"); }
        if i%6 == 0 { p = true; print!("e"); }
        if p {
            println!("");
        } else {
            println!("{}", i);
        }
    }
}
