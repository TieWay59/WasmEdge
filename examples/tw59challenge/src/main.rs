//! How to use this crate
//! # Adding this as a dependency
//! ```rust, ignore
//! [dependencies]
//! wasmedge_hostfunctionexample_interface = "^1.0.0"
//! ```
//!
//! # Bringing this into scope
//! ```rust, ignore
//! use wasmedge_hostfunctionexample_interface::*;
//! ```

use std::ffi::CString;

pub mod wasmedge_hostfunctionexample {
    use std::os::raw::c_char;
    #[link(wasm_import_module = "host_function_example")]
    extern "C" {
        pub fn host_function_example_set_class_id(cid: u32);
        pub fn host_function_example_add_student(student: *const c_char, len: u32) -> u32;
        pub fn host_function_example_set_class_name(name: *const c_char, len: u32);
        pub fn host_function_example_print();
        pub fn host_function_example_binary_gcd(a: u32, b: u32) -> u32;
    }
}

pub fn set_class_id(cid: u32) {
    unsafe {
        wasmedge_hostfunctionexample::host_function_example_set_class_id(cid);
    }
}

pub fn set_class_name<S: AsRef<str>>(name: S) {
    let name = CString::new((name.as_ref()).as_bytes()).expect("");
    unsafe {
        wasmedge_hostfunctionexample::host_function_example_set_class_name(
            name.as_ptr(),
            name.as_bytes().len() as u32,
        );
    }
}

pub fn add_student<S: AsRef<str>>(name: S) -> u32 {
    let name = CString::new((name.as_ref()).as_bytes()).expect("");
    let student_size: u32;
    unsafe {
        student_size = wasmedge_hostfunctionexample::host_function_example_add_student(
            name.as_ptr(),
            name.as_bytes().len() as u32,
        );
    }
    student_size
}

pub fn print() {
    unsafe {
        wasmedge_hostfunctionexample::host_function_example_print();
    }
}

pub fn binary_gcd(a: u32, b: u32) -> u32 {
    unsafe { wasmedge_hostfunctionexample::host_function_example_binary_gcd(a, b) }
}

fn main() {
    // test example function
    set_class_id(101);
    set_class_name("WasmEdge");
    ["Peter", "Paul", "Marry"].iter().for_each(|s| {
        println!("add {}, student number = {}", s, add_student(*s));
    });
    print();

    dbg!(binary_gcd(2, 2));
    dbg!(binary_gcd(2, 4));
    dbg!(binary_gcd(12, 16));
    dbg!(binary_gcd(111111111, 111111112));
}
