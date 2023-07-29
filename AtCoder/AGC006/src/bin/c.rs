use itertools::Itertools;
use proconio::input;
use proconio::marker::Usize1;

fn mul(a: &Vec<usize>, b: &Vec<usize>) -> Vec<usize> {
    (0..a.len()).map(|i| b[a[i]]).collect_vec()
}

fn pow(a: &Vec<usize>, p: i64) -> Vec<usize> {
    if p == 0 {
        (0..a.len()).collect_vec()
    } else {
        let base = pow(a, p / 2);
        let res = mul(&base, &base);
        if p % 2 == 0 {
            res
        } else {
            mul(&res, a)
        }
    }
}

fn main() {
    input! {
        n:usize, x:[i64;n],
        m:usize, k:i64, a:[Usize1;m]
    }
    let dif = (0..n - 1).map(|i| x[i + 1] - x[i]).collect_vec();
    let mut perm = (0..n - 1).collect_vec();
    for i in a {
        perm.swap(i - 1, i);
    }
    let mut res = x[0];
    println!("{}", res);
    for &p in &pow(&perm, k) {
        res += dif[p];
        println!("{}", res);
    }
}
