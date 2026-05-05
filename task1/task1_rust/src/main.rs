use std::io;


fn main() {
    let mut y: f32;
    let mut x: f32 = -5.0;
    println!("x    y");
    while x <= 6.0{
        y = if x <= -1.0 {-2.0 - x}
        else if x >= -1.0 && x < 0.0 {(1.0 - x * x).sqrt() -1.0}
        else if x>= 0.0 && x<=2.0 {2.0 - (4.0 -(x*x)).sqrt()}
        else if x >=2.0 && x <=4.0 {-1.0}
        else if x >= 4.0 && x <= 6.0 {0.5 * x - 3.0}
        else {continue;};
    println!("{x}   {y}");
    x+=1.0;
    }
}

