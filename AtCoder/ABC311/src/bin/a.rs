use proconio::input;

fn main() {
    input! { _: usize, s: String }
    println!(
        "{}",
        s.find('A')
            .unwrap()
            .max(s.find('B').unwrap())
            .max(s.find('C').unwrap())
            + 1
    );
}
