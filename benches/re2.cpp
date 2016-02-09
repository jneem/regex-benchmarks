#include <re2/re2.h>
#include <cstdio>
#include <stdint.h>
#include <string>
#include <time.h>

struct BenchSpec {
    const char *name;
    const char *re;
};

const int NUM_TWAIN_BENCHES = 17;

const struct BenchSpec TWAIN_BENCHES[NUM_TWAIN_BENCHES] = {
    { "twain_00", "Twain" },
    { "twain_01", "(?i)Twain" },
    { "twain_02", "[a-z]shing" },
    { "twain_03", "Huck[a-zA-Z]+|Saw[a-zA-Z]+" },
    { "twain_04a", "\\b\\w+nn\\b" },
    { "twain_04b", "\\bF\\w+n\\b" },
    { "twain_05", "[a-q][^u-z]{13}x" },
    { "twain_06a", "Tom|Sawyer|Huckleberry|Finn" },
    { "twain_06b", "Tom|Twain" },
    { "twain_07", "(?i)Tom|Sawyer|Huckleberry|Finn" },
    { "twain_08", ".{0,2}(Tom|Sawyer|Huckleberry|Finn)" },
    { "twain_09", ".{2,4}(Tom|Sawyer|Huckleberry|Finn)" },
    { "twain_10", "Tom.{10,25}river|river.{10,25}Tom" },
    { "twain_11", "[a-zA-Z]+ing" },
    { "twain_12", "\\s[a-zA-Z]{0,12}ing\\s" },
    { "twain_13", "([A-Za-z]awyer|[A-Za-z]inn)\\s" },
    { "twain_14", "[\"'][^\"']{0,30}[?!\\.][\"']" },
};

const int NUM_GREEK_BENCHES = 16;

const struct BenchSpec GREEK_BENCHES[NUM_GREEK_BENCHES] = {
    { "greek_00", "Δαυιδ" },
    { "greek_01", "(?i)Δαυιδ" },
    { "greek_02", "[α-ω]ρσεν" },
    { "greek_03", "Ἰησ[α-ωΑ-Ω]+|Δαυ[α-ωΑ-Ω]+" },
    { "greek_04a", "\\b\\w+ιδ\\b" }, // TODO: double check that these are working...
    { "greek_04b", "\\bΔ\\w+δ\\b" },
    { "greek_05", "[α-ν][^υ-ω]{13}χ" },
    { "greek_06a", "Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ" },
    { "greek_06b", "Μωυσῆς|Μαριαμ" },
    { "greek_07", "(?i)Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ" },
    { "greek_08", ".{0,2}Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ" },
    { "greek_09", ".{2,4}Ἰησοῦς|Δαυιδ|Μωυσῆς|Μαριαμ" },
    { "greek_10", "Δαυιδ.{10,25}θυσ|θυσ.{10,25}Δαυιδ" },
    { "greek_11", "\\p{Greek}+αις" },
    { "greek_12", "\\s\\p{Greek}{0,12}αις\\s" },
    { "greek_13", "\\p{Greek}ησοῦς|\\p{Greek}αυιδ" },
};

uint64_t ns()
{
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return (uint64_t) tp.tv_sec*1000*1000*1000 + tp.tv_nsec;
}

uint64_t run_bench(std::string &input, const char *re)
{
    RE2 pattern(re);
    int count;
    long time = 0;
    long ITERS = 10;

    for (int i = 0; i < ITERS; i++) {
        count = 0;
        re2::StringPiece in(input);
        long start = ns();
        while (RE2::FindAndConsume(&in, pattern)) {
            count += 1;
        }
        //printf("found %d matches for %s\n", count, re);
        long end = ns();
        time += end - start;
    }

    return time / ITERS;
}

std::string slurp(const char *file_name)
{
    std::FILE *fp = std::fopen(file_name, "r");
    if (!fp) {
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    std::string contents;
    contents.resize(size);
    std::fread(&contents[0], 1, contents.size(), fp);
    std::fclose(fp);

    return contents;
}

int main()
{
    std::string twain = slurp("pg3200.txt");
    std::string greek = slurp("septuagint.txt");

    for (int i = 0; i < NUM_GREEK_BENCHES; i++) {
        uint64_t time = run_bench(greek, GREEK_BENCHES[i].re);
        printf("test %s\t... bench:\t%'ld ns/iter (+/- 0) = %d MB/s\n",
                GREEK_BENCHES[i].name, time, greek.length() * (1000 * 1000 * 1000 / 1024 / 1024) / time);
    }
    for (int i = 0; i < NUM_TWAIN_BENCHES; i++) {
        uint64_t time = run_bench(twain, TWAIN_BENCHES[i].re);
        printf("test %s\t... bench:\t%'ld ns/iter (+/- 0) = %d MB/s\n",
                TWAIN_BENCHES[i].name, time, greek.length() * (1000 * 1000 * 1000 / 1024 / 1024) / time);
    }
}

