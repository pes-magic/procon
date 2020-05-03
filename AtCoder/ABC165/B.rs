use proconio::input;

fn main() {
    input! {
        x : u64
    };
    let mut c = 100;
    let mut res = 0;
    while c < x {
        res += 1;
        c += c/100;
    }
    println!("{}", res);
}
