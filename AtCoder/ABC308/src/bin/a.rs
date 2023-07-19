use proconio::input;

fn valid(a: &Vec<u32>) -> bool {
    for i in 0..a.len() - 1 {
        if a[i] > a[i + 1] {
            return false;
        }
    }
    a.iter().all(|&a| a % 25 == 0 && 100 <= a && a <= 675)
}

fn main() {
    input! {
        a: [u32; 8]
    }
    println!("{}", if valid(&a) { "Yes" } else { "No" });
}
