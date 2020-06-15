use proconio::input;

fn main() {
    input! {
        n : usize,
        mut a : [usize; n]
    };
    a.sort();
    let mut check = [0; 1000001];
    let mut res = 0;
    for i in 0..n {
        if check[a[i]] != 0 { continue }
        if i == n-1 || a[i] != a[i+1] { res += 1 }
        let mut idx = a[i];
        while idx <= 1000000 {
            check[idx] = 1;
            idx += a[i];
        }
    }
    println!("{}", res);
}
