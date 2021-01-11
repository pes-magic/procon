fn main() {
    proconio::input! {
        n: usize,
        a: [i32; 1<<n]
    }
    let half = (1<<n)/2;
    let mut v0 = 0;
    let mut v1 = 0;
    for i in 0..half {
        v0 = v0.max(a[i]);
        v1 = v1.max(a[i+half]);
    }
    for i in 0..1<<n {
        if a[i] == v0.min(v1) {
            println!("{}", i+1);
        }
    }
}
