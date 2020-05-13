use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let mut c = vec![Vec::new(); n];
    for i in 0..m {
        let p = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let y = it.next().unwrap().parse::<i32>().unwrap();
        c[p].push((y, i));
    }
    let mut id = vec![(0, 0); m];
    for i in 0..n {
        c[i].sort();
        for j in 0..c[i].len() {
            id[c[i][j].1] = (i+1, j+1);
        }
    }
    for &p in &id {
        println!("{:06}{:06}", p.0, p.1);
    }
}
