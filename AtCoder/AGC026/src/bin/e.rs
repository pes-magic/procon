use proconio::input;

fn separate(s: &str) -> Vec<&str> {
    let mut res = Vec::new();
    let mut prev = 0;
    let mut sum = 0;
    let sv = s
        .chars()
        .map(|c| if c == 'a' { 1 } else { -1 })
        .collect::<Vec<i32>>();
    for (i, v) in sv.iter().enumerate() {
        sum += v;
        if sum == 0 {
            res.push(&s[prev..=i]);
            prev = i + 1;
        }
    }
    res
}

fn solve_part(s: &str) -> String {
    if s.starts_with("a") {
        let mut dp = vec![0; s.len() + 1];
        let pos_b: Vec<usize> = s
            .chars()
            .enumerate()
            .filter(|&(_, c)| c == 'b')
            .map(|(i, _)| i)
            .collect();
        let mut cnt_a = 0;
        for (i, c) in s.chars().enumerate() {
            dp[i + 1] = dp[i].max(dp[i + 1]);
            if c == 'a' {
                dp[pos_b[cnt_a]] = dp[pos_b[cnt_a]].max(dp[i] + 1);
                cnt_a += 1;
            }
        }
        let res: String = std::iter::repeat("ab").take(dp[s.len()]).collect();
        res
    } else {
        let mut order = vec![0; s.len()];
        let mut cnt = [0, 0];
        for (i, c) in s.chars().enumerate() {
            let idx = c as usize - 'a' as usize;
            order[i] = cnt[idx];
            cnt[idx] += 1;
        }
        let mut res = "".to_string();
        for i in 0..s.len() / 2 {
            let mut tmp = String::new();
            for (j, c) in s.chars().enumerate() {
                if order[j] >= i {
                    tmp.push(c);
                }
            }
            res = std::cmp::max(res, tmp);
        }
        res
    }
}

fn main() {
    input! {
        _: usize,
        s: String
    }
    let vs = separate(&s);
    let mut res = String::new();
    for &s in vs.iter().rev() {
        let tmp = solve_part(s) + &res;
        res = std::cmp::max(res, tmp);
    }
    println!("{}", res);
}
