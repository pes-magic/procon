use std::io::Write;

fn read_value() -> usize {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    line.split_whitespace().next().unwrap().parse::<usize>().unwrap()
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).unwrap();
    let mut it = buf.split_whitespace();
    let case_num = it.next().unwrap().parse::<usize>().unwrap();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let _q = it.next().unwrap().parse::<usize>().unwrap();
    let mut a : Vec<usize> = (0..n).map(|i| i+1).collect();
    for _ in 0..case_num {
        for i in 2..n {
            let mut l = 0;
            let mut r = i+1;
            while r-l >= 2 {
                let mut mid = (l+r)/2;
                mid = mid.min(i-1);
                println!("{} {} {}", a[mid-1], a[mid], a[i]);
                std::io::stdout().flush().unwrap();
                let res = read_value();
                if res == a[i] {
                    l = mid;
                    r = mid+1;
                } else if res == a[mid-1] {
                    r = mid;
                } else {
                    l = mid+1;
                }
            }
            for j in (l..i).rev() {
                let tmp = a[j+1];
                a[j+1] = a[j];
                a[j] = tmp;
            }
        }
        for i in 0..n-1 { print!("{} ", a[i]) }
        println!("{}", a[n-1]);
        std::io::stdout().flush().unwrap();
        read_value();
    }
}
