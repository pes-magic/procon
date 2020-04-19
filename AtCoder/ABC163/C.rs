use proconio::input;

fn main() {
    input! {
        n : usize,
        a : [usize; n-1]
    };
    let mut res = vec!(0; n);
    for i in a {
        res[i-1] += 1;
    }
    for t in res { println!("{}", t); }
}
