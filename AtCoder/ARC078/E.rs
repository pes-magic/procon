fn main() {
    let mut res : i64 = 0;
    for i in 0..15 {
        let mut low : i64 = if res > 0 { -1 } else { 0 };
        let mut high : i64 = 9;
        while high - low > 1 {
            let mid = (low + high) / 2;
            if i < 5 {
                println!("? {}9999999999", 10*res+mid);
            } else {
                println!("? {}999999", 10*res+mid);
            }
            let mut buf = String::new();
            std::io::stdin().read_line(&mut buf).ok();
            if &buf[0..1] == "Y" {
                high = mid;
            } else {
                low = mid;
            }
        }
        res = 10 * res + high;
        println!("? {}", res+1);
        let str_cmp = res.to_string() < (res+1).to_string();
        {
            let mut buf = String::new();
            std::io::stdin().read_line(&mut buf).ok();
            if str_cmp == (&buf[0..1] == "Y") {
                println!("! {}", res);
                break;
            }
        }
    }
}
