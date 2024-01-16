use std::process::Command;
use std::str;

pub fn eselect_kernel_list() -> Vec<String> {
    let out: Vec<u8> = Command::new("/usr/bin/eselect")
        .arg("kernel")
        .arg("list")
        .output()
        .expect("Failed to execute eselect kernel list")
        .stdout;

    match str::from_utf8(&out.clone()) {
        Ok(v) => v,
        Err(e) => panic!("invalid utf8 sequence in eselect kernel list: {}", e),
    }.split('\n').collect::<Vec<&str>>().iter().map(|e| e.to_string()).collect() // holy hell
}
