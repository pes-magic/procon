use proconio::input;
fn main() {
    input! {
        n:usize, l:i64, t:i64,
        info: [(i64, i64);n]
    }
    let mut cnt = 0;
    for i in 1..n {
        if info[0].1 == info[i].1 {
            continue;
        }
        let mut pos1 = info[0].0;
        let mut pos2 = info[i].0;
        if info[0].1 == 2 {
            std::mem::swap(&mut pos1, &mut pos2);
        }
        if pos2 < pos1 {
            pos2 += l;
        }
        let first = pos2 - pos1;
        if 2 * t >= first {
            cnt += 1 + (2 * t - first) / l;
        }
    }
    cnt %= n as i64;
    let target = if info[0].1 == 1 {
        cnt as usize % n
    } else {
        (n - cnt as usize) % n
    };
    let mut last = Vec::new();
    let mut pos0 = 0;
    for i in 0..n {
        if info[i].1 == 1 {
            let pos = (info[i].0 + t) % l;
            if i == 0 {
                pos0 = pos;
            }
            last.push((pos, -1));
        } else {
            let pos = (info[i].0 + l - t % l) % l;
            if i == 0 {
                pos0 = pos;
            }
            last.push((pos, -2));
        }
    }
    last.sort();
    let mut res = vec![0; n];
    for i in 0..n {
        if last[i].0 == pos0 && -last[i].1 == info[0].1 {
            for j in 0..n {
                res[(target + j) % n] = last[(i + j) % n].0;
            }
            break;
        }
    }
    for &r in &res {
        println!("{}", r);
    }
}
