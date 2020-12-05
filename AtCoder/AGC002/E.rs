fn main() {
    proconio::input! {
        n: usize,
        mut a: [usize; n]
    }
    a.sort();
    let mut dp = vec![(0, a[0]); 1];
    for i in 1..n {
        if (a[i]-a[i-1])%2 == 1 {
            dp.push((1, 1));
        } else {
            dp.push((1-dp.last().unwrap().0, 1));
        }
        if a[i-1] < a[i] {
            dp.push((0, a[i]-a[i-1]));
        }
    }
    dp.reverse();
    let mut sum = 0;
    for &p in &dp {
        if sum + p.1 < a[n-1] {
            sum += p.1;
        } else {
            let pos = 1 - (a[n-1] - sum)%2;
            println!("{}", if (pos + p.0)%2 == 1 { "First" } else { "Second" });
            break
        }
    }
}
