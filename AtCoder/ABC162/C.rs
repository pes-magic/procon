use proconio::input;
use num::Integer;

fn main() {
    input! {
        K : u32
    };
    let mut res = 0;
    for i in 1..=K {
        for j in 1..=K {
            for k in 1..=K {
                res += i.gcd(&j).gcd(&k);
            }
        }
    }
    println!("{}", res);
}
