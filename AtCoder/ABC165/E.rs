use proconio::input;

fn main() {
    input! {
        (n, m) : (usize, usize)
    };
    let mo = m - 1 + m%2;
    let me = m/2*2;
    for i in 0..n {
        if i >= mo - i { break; }
        println!("{} {}", i+1, mo+1-i);
    }
    for i in 0..n {
        if i >= me - i { break; }
        println!("{} {}", mo+i+2, mo+2+me-i);
    }
}
