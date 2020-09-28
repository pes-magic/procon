fn solve(n: i32) -> i32 {
    for i in 1..=n {
        if i*i > n { return i-1 }
    }
    n
}

fn main() {
    proconio::input! {
        n: i32
    }
    println!("{}", solve(n));
}
