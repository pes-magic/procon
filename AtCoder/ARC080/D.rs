use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let h = it.next().unwrap().parse::<usize>().unwrap();
    let w = it.next().unwrap().parse::<usize>().unwrap();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut a = (0..n).map(|_| it.next().unwrap().parse::<usize>().unwrap()).collect::<Vec<_>>();
    let mut res = vec![vec![0; w]; h];
    let mut color = 0;
    for i in 0..h {
        for j in 0..w {
            if a[color] == 0 { color = color + 1 }
            a[color] -= 1;
            res[i][if i%2 == 0 { j } else { w-1-j }] = color + 1;
        }
    }
    for i in 0..h {
        print!("{}", res[i][0]);
        for j in 1..w { print!(" {}", res[i][j]); }
        println!("");
    }
}
