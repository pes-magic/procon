use proconio::input;

fn main(){
    input! {
        n : usize,
        c : i128,
        x : [i128; n]
    };
    let mut s = vec![0; n+1];
    for i in 0..n { s[i+1] = s[i] + x[i]; }
    let mut res = 1 << 120;
    for i in 1..=n {
        let mut cur = (n+i) as i128 * c;
        for j in 0..=n {
            if i*j >= n { break }
            let src = n - j*i;
            let dst = if src >= i { src - i } else { 0 };
            cur += (s[src] - s[dst]) * std::cmp::max(5, 2*j+3) as i128;
        }
        res = std::cmp::min(res, cur);
    }
    println!("{}", res);
}