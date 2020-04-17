use proconio::input;

fn main(){
    input! {
        n : usize,
        s : String
    };
    let r = s.match_indices("R").count();
    let g = s.match_indices("G").count();
    let b = s.match_indices("B").count();
    let c = s.as_bytes();
    let mut res = r * g * b;
    for i in 0..n {
        for j in 1..n {
            if i + 2 * j >= n { break }
            if c[i] != c[i+j] && c[i+j] != c[i+2*j] && c[i+2*j] != c[i] {
                res -= 1;
            }
        }
    }
    println!("{}", res);
}