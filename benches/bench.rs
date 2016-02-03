#![feature(test)]

extern crate regex;
extern crate test;

use regex::Regex;
use test::Bencher;

const HAYSTACK: &'static str = include_str!("pg3200.txt");

macro_rules! search(
    ($name:ident, $re:expr) => (
        #[bench]
        fn $name(b: &mut Bencher) {
            let re = Regex::new($re).unwrap();
            b.bytes = HAYSTACK.len() as u64;
            b.iter(|| re.find_iter(HAYSTACK).count());
        }
    );
);

search!(twain_00, r#"Twain"#);
search!(twain_01, r#"(?i)Twain"#);
search!(twain_02, r#"[a-z]shing"#);
search!(twain_03, r#"Huck[a-zA-Z]+|Saw[a-zA-Z]+"#);
search!(twain_04a, r#"\b\w+nn\b"#);
search!(twain_04b, r#"\bF\w+n\b"#);
search!(twain_05, r#"[a-q][^u-z]{13}x"#);
search!(twain_06a, r#"Tom|Sawyer|Huckleberry|Finn"#);
search!(twain_06b, r#"Tom|Twain"#);
search!(twain_07, r#"(?i)Tom|Sawyer|Huckleberry|Finn"#);
search!(twain_08, r#".{0,2}(Tom|Sawyer|Huckleberry|Finn)"#);
search!(twain_09, r#".{2,4}(Tom|Sawyer|Huckleberry|Finn)"#);
search!(twain_10, r#"Tom.{10,25}river|river.{10,25}Tom"#);
search!(twain_11, r#"[a-zA-Z]+ing"#);
search!(twain_12, r#"\s[a-zA-Z]{0,12}ing\s"#);
search!(twain_13, r#"([A-Za-z]awyer|[A-Za-z]inn)\s"#);
search!(twain_14, r#"["'][^"']{0,30}[?!\.]["']"#);

