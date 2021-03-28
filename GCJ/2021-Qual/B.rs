use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let case_num = it.next().unwrap().parse::<usize>().unwrap();
    for t in 0..case_num {
        let x = it.next().unwrap().parse::<i64>().unwrap();
        let y = it.next().unwrap().parse::<i64>().unwrap();
        let s = it.next().unwrap().as_bytes();
        let mut dp = vec![[(1 as i64) << 30; 2]; s.len()];
        if s[0] != 'J' as u8 { dp[0][0] = 0 }
        if s[0] != 'C' as u8 { dp[0][1] = 0 }
        for i in 1..s.len() {
            if s[i] != 'J' as u8 { dp[i][0] = dp[i-1][0].min(dp[i-1][1] + y); }
            if s[i] != 'C' as u8 { dp[i][1] = dp[i-1][1].min(dp[i-1][0] + x); }
        }
        println!("Case #{}: {}", t+1, dp[s.len()-1][0].min(dp[s.len()-1][1]));
    }
}
