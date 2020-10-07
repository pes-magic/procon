fn cnt(c: &Vec<usize>) -> Vec<usize> {
    let mut res = vec![0; c.len()+1];
    for &t in c { res[t] += 1 }
    for i in 0..c.len() { res[i+1] += res[i]; }
    res
}

fn main() {
    proconio::input! {
        n: usize,
        a: [usize; n],
        b: [usize; n]
    }
    let ca = cnt(&a);
    let cb = cnt(&b);
    let mut d = 0;
    for i in 0..n {
        if ca[i+1] > cb[i] { d = d.max(ca[i+1]-cb[i]) }
    }
    let mut ok = true;
    for i in 0..n {
        if a[i] == b[(i+n-d)%n] { ok = false }
    }
    if ok {
        println!("Yes");
        for i in 0..n { print!("{} ", b[(i+n-d)%n]) }
        println!("");
    } else {
        println!("No");
    }
}
