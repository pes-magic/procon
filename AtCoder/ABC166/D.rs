use proconio::input;
use num::pow;

fn solve(x: i64) -> (i64, i64) {
    for i in 1..200 {
        for j in -200..200 {
            if pow(i, 5) - pow(j, 5) == x {
                return (i, j);
            }
        }
    }
    (0, 0)
}

fn main(){
    input!{
        x : i64
    };
    let res = solve(x);
    println!("{} {}", res.0, res.1);
}