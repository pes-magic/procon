fn solve(k: usize) -> i32 {
    let mut cur = 7 % k;
    let mut res = 1;
    let mut see = vec![0; k];
    loop {
        if see[cur] == 1 { break }
        if cur == 0 { return res }
        see[cur] = 1;
        cur = (10 * cur + 7) % k;
        res += 1;
    }
    -1
}

fn main() {
    proconio::input! {
        k: usize
    }
    println!("{}", solve(k));
}
