This is a dumping-ground for some regular expression benchmarking code. So far, I'm comparing my
[https://github.com/jneem/regex-dfa](`regex-dfa`) crate, the [https://github.com/rust-lang-nursery/regex/tree/dfa](`dfa` branch)
of rust's official `regex` crate, and Google's `RE2`. The input texts are large natural language texts: the complete
works of Mark Twain and the old testament in Greek.

My `regex-dfa` crate: 
```
test greek_00  ... bench:  10,314,649 ns/iter (+/- 42,475) = 763 MB/s
test greek_01  ... bench:  30,356,180 ns/iter (+/- 263,859) = 259 MB/s
test greek_02  ... bench:  19,381,521 ns/iter (+/- 304,912) = 406 MB/s
test greek_03  ... bench:  20,608,494 ns/iter (+/- 117,083) = 382 MB/s
test greek_04a ... bench:  20,808,451 ns/iter (+/- 107,572) = 378 MB/s
test greek_04b ... bench:  20,734,729 ns/iter (+/- 255,238) = 379 MB/s
test greek_05  ... bench: 121,949,502 ns/iter (+/- 1,160,707) = 64 MB/s
test greek_06a ... bench:  20,340,626 ns/iter (+/- 271,528) = 387 MB/s
test greek_06b ... bench:  16,694,565 ns/iter (+/- 1,082,825) = 471 MB/s
test greek_07  ... bench:  20,793,428 ns/iter (+/- 264,304) = 378 MB/s
test greek_08  ... bench:  20,815,363 ns/iter (+/- 306,256) = 378 MB/s
test greek_09  ... bench:  20,854,125 ns/iter (+/- 273,423) = 377 MB/s
test greek_10  ... bench:  16,971,940 ns/iter (+/- 1,221,579) = 464 MB/s
test greek_11  ... bench:  20,795,045 ns/iter (+/- 260,789) = 378 MB/s
test greek_12  ... bench:  21,502,893 ns/iter (+/- 368,654) = 366 MB/s
test greek_13  ... bench:  20,542,432 ns/iter (+/- 231,711) = 383 MB/s
test twain_00  ... bench:   1,856,173 ns/iter (+/- 35,920) = 8627 MB/s
test twain_01  ... bench:  40,994,819 ns/iter (+/- 4,427,111) = 390 MB/s
test twain_02  ... bench:  39,846,801 ns/iter (+/- 2,578,927) = 401 MB/s
test twain_03  ... bench:  41,797,565 ns/iter (+/- 3,423,057) = 383 MB/s
test twain_04a ... bench:  41,457,414 ns/iter (+/- 3,309,836) = 386 MB/s
test twain_04b ... bench:  41,940,752 ns/iter (+/- 2,744,174) = 381 MB/s
test twain_05  ... bench: 299,424,820 ns/iter (+/- 22,209,259) = 53 MB/s
test twain_06a ... bench:  40,295,464 ns/iter (+/- 236,676) = 397 MB/s
test twain_06b ... bench:   3,371,603 ns/iter (+/- 66,502) = 4749 MB/s
test twain_07  ... bench:  42,332,353 ns/iter (+/- 360,798) = 378 MB/s
test twain_08  ... bench:  42,184,960 ns/iter (+/- 297,927) = 379 MB/s
test twain_09  ... bench:  41,914,128 ns/iter (+/- 419,106) = 382 MB/s
test twain_10  ... bench:  38,915,064 ns/iter (+/- 423,970) = 411 MB/s
test twain_11  ... bench:  90,479,905 ns/iter (+/- 4,383,234) = 176 MB/s
test twain_12  ... bench:  79,315,507 ns/iter (+/- 4,574,498) = 201 MB/s
test twain_13  ... bench:  40,703,191 ns/iter (+/- 4,033,156) = 393 MB/s
test twain_14  ... bench:  51,095,552 ns/iter (+/- 4,131,255) = 313 MB/s
```

The `dfa` branch of the `regex` crate:
```
test greek_00  ... bench:  10,654,105 ns/iter (+/- 40,786) = 739 MB/s
test greek_01  ... bench:  18,601,086 ns/iter (+/- 85,727) = 423 MB/s
test greek_02  ... bench:  19,146,986 ns/iter (+/- 110,917) = 411 MB/s
test greek_03  ... bench:  19,497,563 ns/iter (+/- 121,347) = 403 MB/s
test greek_04a ... bench: 477,485,680 ns/iter (+/- 18,003,451) = 16 MB/s
test greek_04b ... bench: 318,780,084 ns/iter (+/- 1,213,259) = 24 MB/s
test greek_05  ... bench: 311,811,965 ns/iter (+/- 7,215,804) = 25 MB/s
test greek_06a ... bench:  19,698,876 ns/iter (+/- 261,094) = 399 MB/s
test greek_06b ... bench:  16,278,084 ns/iter (+/- 8,394,386) = 483 MB/s
test greek_07  ... bench:  25,196,789 ns/iter (+/- 3,583,122) = 312 MB/s
test greek_08  ... bench:  37,921,335 ns/iter (+/- 22,366,619) = 207 MB/s
test greek_09  ... bench:  37,966,985 ns/iter (+/- 22,329,358) = 207 MB/s
test greek_10  ... bench:  17,886,813 ns/iter (+/- 9,148,246) = 440 MB/s
test greek_11  ... bench:  62,180,494 ns/iter (+/- 30,852,592) = 126 MB/s
test greek_12  ... bench:  40,376,051 ns/iter (+/- 26,174,827) = 195 MB/s
test greek_13  ... bench:  37,880,270 ns/iter (+/- 21,883,741) = 207 MB/s
test twain_00  ... bench:   1,893,920 ns/iter (+/- 27,704) = 8455 MB/s
test twain_01  ... bench:  38,957,410 ns/iter (+/- 108,795) = 411 MB/s
test twain_02  ... bench:  39,459,312 ns/iter (+/- 83,155) = 405 MB/s
test twain_03  ... bench:  38,992,753 ns/iter (+/- 69,725) = 410 MB/s
test twain_04a ... bench: 1,190,391,552 ns/iter (+/- 330,034,527) = 13 MB/s
test twain_04b ... bench: 769,074,188 ns/iter (+/- 7,159,106) = 20 MB/s
test twain_05  ... bench: 333,861,203 ns/iter (+/- 12,923,765) = 47 MB/s
test twain_06a ... bench:  39,538,557 ns/iter (+/- 167,312) = 405 MB/s
test twain_06b ... bench:   2,568,582 ns/iter (+/- 44,805) = 6234 MB/s
test twain_07  ... bench: 104,415,847 ns/iter (+/- 682,257) = 153 MB/s
test twain_08  ... bench:  77,142,416 ns/iter (+/- 1,174,675) = 207 MB/s
test twain_09  ... bench:  77,073,166 ns/iter (+/- 1,619,581) = 207 MB/s
test twain_10  ... bench:  39,788,995 ns/iter (+/- 628,114) = 402 MB/s
test twain_11  ... bench:  91,974,308 ns/iter (+/- 607,039) = 174 MB/s
test twain_12  ... bench: 100,839,189 ns/iter (+/- 522,775) = 158 MB/s
test twain_13  ... bench: 165,131,943 ns/iter (+/- 405,959) = 96 MB/s
test twain_14  ... bench:  23,139,195 ns/iter (+/- 113,653) = 692 MB/s
```
The slowness of `(greek|twain)_04[ab]` compared to my `regex-dfa` crate is
because `regex` doesn't support word boundaries in its DFA engine.

Google's `RE2` (ignore the +/- part, it's bogus):
```
test greek_00	... bench:	15585711 ns/iter (+/- 0) = 481 MB/s
test greek_01	... bench:	16446975 ns/iter (+/- 0) = 456 MB/s
test greek_02	... bench:	39095792 ns/iter (+/- 0) = 191 MB/s
test greek_03	... bench:	53448964 ns/iter (+/- 0) = 140 MB/s
test greek_04a	... bench:	22651633 ns/iter (+/- 0) = 331 MB/s
test greek_04b	... bench:	22624291 ns/iter (+/- 0) = 331 MB/s
test greek_05	... bench:	7506586482 ns/iter (+/- 0) = 0 MB/s
test greek_06a	... bench:	56242344 ns/iter (+/- 0) = 133 MB/s
test greek_06b	... bench:	15008596 ns/iter (+/- 0) = 500 MB/s
test greek_07	... bench:	57060549 ns/iter (+/- 0) = 131 MB/s
test greek_08	... bench:	31711728 ns/iter (+/- 0) = 236 MB/s
test greek_09	... bench:	31380833 ns/iter (+/- 0) = 239 MB/s
test greek_10	... bench:	14189040 ns/iter (+/- 0) = 528 MB/s
test greek_11	... bench:	46204006 ns/iter (+/- 0) = 162 MB/s
test greek_12	... bench:	29465292 ns/iter (+/- 0) = 254 MB/s
test greek_13	... bench:	35924720 ns/iter (+/- 0) = 208 MB/s
test twain_00	... bench:	2068592 ns/iter (+/- 0) = 3628 MB/s
test twain_01	... bench:	74399332 ns/iter (+/- 0) = 100 MB/s
test twain_02	... bench:	125666830 ns/iter (+/- 0) = 59 MB/s
test twain_03	... bench:	61796312 ns/iter (+/- 0) = 121 MB/s
test twain_04a	... bench:	52680387 ns/iter (+/- 0) = 142 MB/s
test twain_04b	... bench:	59633073 ns/iter (+/- 0) = 125 MB/s
test twain_05	... bench:	23434722253 ns/iter (+/- 0) = 0 MB/s
test twain_06a	... bench:	69413009 ns/iter (+/- 0) = 108 MB/s
test twain_06b	... bench:	2780574 ns/iter (+/- 0) = 2699 MB/s
test twain_07	... bench:	117541533 ns/iter (+/- 0) = 63 MB/s
test twain_08	... bench:	59999945 ns/iter (+/- 0) = 125 MB/s
test twain_09	... bench:	58497320 ns/iter (+/- 0) = 128 MB/s
test twain_10	... bench:	61719232 ns/iter (+/- 0) = 121 MB/s
test twain_11	... bench:	107277706 ns/iter (+/- 0) = 69 MB/s
test twain_12	... bench:	77512406 ns/iter (+/- 0) = 96 MB/s
test twain_13	... bench:	89653202 ns/iter (+/- 0) = 83 MB/s
test twain_14	... bench:	86079974 ns/iter (+/- 0) = 87 MB/s
```
Note how slow `greek_05` and `twain_05` are! I haven't looked too much at what `RE2` is
doing, but maybe its DFA caching needs to be tuned: those two regexes have a huge number
of DFA states.

