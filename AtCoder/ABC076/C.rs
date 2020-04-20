fn main() {
    let mut s = String::new();
    let mut t = String::new();
    std::io::stdin().read_line(&mut s).ok();
    std::io::stdin().read_line(&mut t).ok();
    let a = s.trim_right().as_bytes();
    let b = t.trim_right().as_bytes();
    for i in (0..a.len()).rev() {
        if i + b.len() > a.len() { continue; }
        let mut valid = true;
        for j in 0..b.len() {
            if a[i+j] != '?' as u8 && a[i+j] != b[j] {
                valid = false;
                break;
            }
        }
        if valid {
            for j in 0..i {
                print!("{}", if a[j] == '?' as u8 {"a"} else { &s[j..j+1] } )
            }
            print!("{}", t.trim_right());
            for j in i+b.len()..a.len() {
                print!("{}",  if a[j] == '?' as u8 {"a"} else { &s[j..j+1] } )
            }
            println!("");
            return;
        }
    }
    println!("UNRESTORABLE");
}
