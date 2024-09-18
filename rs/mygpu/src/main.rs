use anyhow::Result;
use log4rs::{
    append::console::ConsoleAppender,
    config::{Appender, Logger, Root},
    encode::pattern::PatternEncoder,
    Config,
};

fn main() -> Result<()> {
    let console_appender = ConsoleAppender::builder()
        .encoder(Box::new(PatternEncoder::new(mygpu::LOG_FORMAT)))
        .build();

    let logging_config = Config::builder()
        .appender(Appender::builder().build("mygpu", Box::new(console_appender)))
        .logger(Logger::builder().build("app::mygpu", mygpu::LOG_LEVEL))
        .build(Root::builder().appender("mygpu").build(mygpu::LOG_LEVEL))?;

    // Use this returned value if a change in configuration happen later.
    let _ = log4rs::init_config(logging_config)?;

    pollster::block_on(mygpu::run());

    Ok(())
}
