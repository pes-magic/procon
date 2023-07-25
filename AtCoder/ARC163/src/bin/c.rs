use itertools::Itertools;
use proconio::input;

fn solve(n: usize) -> Vec<usize> {
    let mut res: Vec<usize> = (1..n).map(|i| i * (i + 1)).collect();
    for &r in &res {
        if r == n {
            let mut res2: Vec<usize> = solve(n - 1).iter().map(|v| 2 * v).collect();
            res2.push(2);
            return res2;
        }
    }
    res.push(n);
    res
}

fn main() {
    input! { n: usize, a: [usize;n] }
    for v in a {
        if v == 1 {
            println!("Yes");
            println!("1");
            continue;
        }
        if v == 2 {
            println!("No");
            continue;
        }
        println!("Yes");
        let res = solve(v);
        println!("{}", res.iter().join(" "));
    }
}
