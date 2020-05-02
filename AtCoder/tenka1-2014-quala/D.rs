use std::f64;
use std::io::Read;

const EPS: f64 = 1e-8;
const PI2: f64 = 2.0 * f64::consts::PI;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut l = Vec::<(f64, f64)>::new();
    let mut rads = Vec::<f64>::new();
    for _ in 0..n {
        let x1 = it.next().unwrap().parse::<f64>().unwrap();
        let y1 = it.next().unwrap().parse::<f64>().unwrap();
        let x2 = it.next().unwrap().parse::<f64>().unwrap();
        let y2 = it.next().unwrap().parse::<f64>().unwrap();
        let mut r = (y1.atan2(x1), y2.atan2(x2));
        if r.1 < r.0 { r = (r.1, r.0); }
        if r.1 - r.0 > f64::consts::PI { r = (r.1, r.0 + PI2); }
        l.push(r);
        rads.push(r.0);
        rads.push(r.1);
    }
    let mut res = n;
    for r in rads {
        let mut rest = Vec::<(f64, f64)>::new();
        for &c in &l {
            if (c.0 - EPS < r && r < c.1 + EPS) || (c.0 + PI2 - EPS < r && r < c.1 + PI2 + EPS) { continue; }
            if c.0 > r { rest.push(c); }
            else { rest.push((c.0 + PI2, c.1 + PI2)); }
        }
        rest.sort_by(|a, b| a.1.partial_cmp(&b.1).unwrap());
        let mut cnt = 1;
        let mut cur = -1e10;
        for &c in &rest {
            if cur + EPS < c.0 {
                cur = c.1;
                cnt += 1;
            }
        }
        res = std::cmp::min(res, cnt);
    }
    println!("{}", res);
}
