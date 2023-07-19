use proconio::input;

fn mex(a: usize, b: usize, c: usize) -> usize {
    for i in 0..3 {
        if a == i || b == i || c == i {
            continue;
        }
        return i;
    }
    3
}

fn main() {
    input! {
        n: usize,
        a: [usize; n],
        s: String
    }
    let mut cnt_m = vec![0; 3];
    let mut cnt_x = vec![0; 3];
    for (i, c) in s.chars().enumerate() {
        if c == 'X' {
            cnt_x[a[i]] += 1;
        }
    }
    let mut res = 0;
    for (i, c) in s.chars().enumerate() {
        match c {
            'M' => {
                cnt_m[a[i]] += 1;
            }
            'E' => {
                for j in 0..3 {
                    for k in 0..3 {
                        res += cnt_m[j] * cnt_x[k] * mex(j, k, a[i]);
                    }
                }
            }
            'X' => {
                cnt_x[a[i]] -= 1;
            }
            _ => {}
        }
    }
    println!("{}", res);
}
