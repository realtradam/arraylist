#[test]
fn arraylist_test(){
    let mut al = Vec::new();
    al.push(10);
    assert_eq!(al.get(0), Some(10));
}