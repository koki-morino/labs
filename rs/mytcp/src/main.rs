use core::str;
use std::{
    env,
    error::Error,
    io::{Read, Write},
    net::TcpListener,
    thread,
};

fn main() -> Result<(), Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    let mut addr = &String::from("127.0.0.1:8080");
    if args.len() < 2 {
        println!(
            "\
            Argument missing\n\
            Fallback to 127.0.0.1:8080\
            "
        );
    } else {
        addr = &args[1];
    }

    listen(addr)?;

    Ok(())
}

fn listen(addr: &str) -> Result<(), Box<dyn Error>> {
    let listener = TcpListener::bind(addr)?;
    loop {
        let (mut stream, _) = listener.accept()?;

        thread::spawn(move || {
            let mut buffer = [0u8; 1024];
            loop {
                let num_bytes = stream.read(&mut buffer).unwrap();
                if num_bytes == 0 {
                    return;
                }

                print!("{}", str::from_utf8(&buffer[..num_bytes]).unwrap());
                stream.write_all(&buffer[..num_bytes]).unwrap();
            }
        });
    }
}
