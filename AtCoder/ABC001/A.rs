fn main(){
    let mut s1 = String::new();
    std::io::stdin().read_line(&mut s1).ok();
    let h1: i32 = s1.trim().parse().ok().unwrap();
    let mut s2 = String::new();
    std::io::stdin().read_line(&mut s2).ok();
    let h2: i32 = s2.trim().parse().ok().unwrap();
    println!("{}", h1 - h2);
}