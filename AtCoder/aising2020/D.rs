use proconio::input;

fn main() {
    input! {
        n: usize,
        x: String
    };
    let s = x.as_bytes();
    let mut cnt = 0;
    for &c in s {
        if c == b'1' { cnt += 1 }
    }
    let mut dp = vec![0; n+1];
    for i in 1..=n as i32 {
        let d = i.count_ones() as i32;
        dp[i as usize] = dp[(i%d) as usize] + 1;
    }
    let mut res = vec![0; n];
    for &d in [-1, 1].iter() {
        let m = cnt + d;
        if m <= 0 || (n as i32) < m { continue }
        let mut p2 = vec![1; n];
        let mut sum = 0;
        for i in (0..n-1).rev() {
            p2[i] = 2*p2[i+1] % m;
        }
        for i in 0..n {
            if s[i] == b'1' { sum = (sum + p2[i]) % m; }
        }
        for i in 0..n {
            if d == -1 {
                if s[i] == b'0' { continue }
                res[i] = dp[((sum+m-p2[i])%m) as usize] + 1;
            } else {
                if s[i] == b'1' { continue }
                res[i] = dp[((sum+p2[i])%m) as usize] + 1;
            }
        }
    }
    for &d in &res {
        println!("{}", d);
    }
}
