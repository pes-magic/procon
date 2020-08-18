fn main() {
    proconio::input! {
        n : usize,
        p : [usize; n]
    };
    let sum = p.iter().fold(0, |x, y| x+y);
    let mut dp = vec![0; sum+1];
    dp[0] = 1;
    for &t in &p {
        for i in (0..=sum-t).rev() {
            if dp[i] == 1 { dp[i+t] = 1 }
        }
    }
    println!("{}", dp.iter().fold(0, |x, y| x+y));
}
