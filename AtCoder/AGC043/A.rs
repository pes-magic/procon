use std::io::Read;
use std::cmp;

fn main(){
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let h = it.next().unwrap().parse::<usize>().unwrap();
    let w = it.next().unwrap().parse::<usize>().unwrap();
    let s = (0..h).map(|_| it.next().unwrap().as_bytes()).collect::<Vec<_>>();
    let mut dp = vec!(vec!(100000; w); h);
    dp[0][0] = if s[0][0] == '#' as u8 { 1 } else { 0 };
    for i in 0..h {
        for j in 0..w {
            if i+1 < h {
                dp[i+1][j] = cmp::min(dp[i+1][j], dp[i][j] + if s[i][j] == '.' as u8 && s[i+1][j] == '#' as u8 { 1 } else { 0 });
            }
            if j+1 < w {
                dp[i][j+1] = cmp::min(dp[i][j+1], dp[i][j] + if s[i][j] == '.' as u8 && s[i][j+1] == '#' as u8 { 1 } else { 0 });
            }
        }
    }
    println!("{}", dp[h-1][w-1]);
}