#![feature(test)]

extern crate regex;
extern crate test;

use regex::Regex;
use test::Bencher;

const TWAIN: &'static str = include_str!("pg3200.txt");
const GREEK: &'static str = include_str!("septuagint.txt");

macro_rules! search(
    ($haystack:expr, $name:ident, $re:expr) => (
        #[bench]
        fn $name(b: &mut Bencher) {
            let re = Regex::new($re).unwrap();
            b.bytes = $haystack.len() as u64;
            b.iter(|| re.find_iter($haystack).count());
        }
    );
);

search!(TWAIN, twain_00, r#"Twain"#);
search!(TWAIN, twain_01, r#"(?i)Twain"#);
search!(TWAIN, twain_02, r#"[a-z]shing"#);
search!(TWAIN, twain_03, r#"Huck[a-zA-Z]+|Saw[a-zA-Z]+"#);
search!(TWAIN, twain_04a, r#"\b\w+nn\b"#);
search!(TWAIN, twain_04b, r#"\bF\w+n\b"#);
search!(TWAIN, twain_05, r#"[a-q][^u-z]{13}x"#);
search!(TWAIN, twain_06a, r#"Tom|Sawyer|Huckleberry|Finn"#);
search!(TWAIN, twain_06b, r#"Tom|Twain"#);
search!(TWAIN, twain_07, r#"(?i)Tom|Sawyer|Huckleberry|Finn"#);
search!(TWAIN, twain_08, r#".{0,2}(Tom|Sawyer|Huckleberry|Finn)"#);
search!(TWAIN, twain_09, r#".{2,4}(Tom|Sawyer|Huckleberry|Finn)"#);
search!(TWAIN, twain_10, r#"Tom.{10,25}river|river.{10,25}Tom"#);
search!(TWAIN, twain_11, r#"[a-zA-Z]+ing"#);
search!(TWAIN, twain_12, r#"\s[a-zA-Z]{0,12}ing\s"#);
search!(TWAIN, twain_13, r#"([A-Za-z]awyer|[A-Za-z]inn)\s"#);
search!(TWAIN, twain_14, r#"["'][^"']{0,30}[?!\.]["']"#);

search!(GREEK, greek_00, r#"Δαυιδ"#);
search!(GREEK, greek_01, r#"(?i)Δαυιδ"#);
search!(GREEK, greek_02, r#"[α-ω]ρσεν"#);
search!(GREEK, greek_03, r#"Ἰησ[α-ωΑ-Ω]+|Δαυ[α-ωΑ-Ω]+"#);
search!(GREEK, greek_04a, r#"\b\w+ιδ\b"#);
search!(GREEK, greek_04b, r#"\bΔ\w+δ\b"#);
search!(GREEK, greek_05, r#"[α-ν][^υ-ω]{13}χ"#);
search!(GREEK, greek_06a, r#"Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ"#);
search!(GREEK, greek_06b, r#"Μωυσῆς|Μαριαμ"#);
search!(GREEK, greek_07, r#"(?i)Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ"#);
search!(GREEK, greek_08, r#".{0,2}Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ"#);
search!(GREEK, greek_09, r#".{2,4}Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ"#);
search!(GREEK, greek_10, r#"Δαυιδ.{10,25}θυσ|θυσ.{10,25}Δαυιδ"#);
search!(GREEK, greek_11, r#"\p{Greek}+αις"#);
search!(GREEK, greek_12, r#"\s\p{Greek}{0,12}αις\s"#);
search!(GREEK, greek_13, r#"\p{Greek}ησοῦς|\p{Greek}αυιδ"#);
