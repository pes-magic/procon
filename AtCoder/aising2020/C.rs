use proconio::input;

fn main() {
    input! {
        n: usize
    }
    let mut res = vec![0; n];
    for i in 1..=100 {
        for j in 1..=100 {
            for k in 1..=100 {
                let v = i*i + j*j + k*k + i*j + j*k + k*i;
                if v <= n { res[v-1] += 1 }
            }
        }
    }
    for &v in &res { println!("{}", v) }
}
