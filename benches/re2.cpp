#include <re2/re2.h>
#include <cstdio>
#include <stdint.h>
#include <string>
#include <time.h>

struct BenchSpec {
    const char *name;
    const char *re;
};

const int NUM_BENCHES = 16;

const struct BenchSpec BENCHES[NUM_BENCHES] = {
    { "twain_00", "Twain" },
    { "twain_01", "(?i)Twain" },
    { "twain_02", "[a-z]shing" },
    { "twain_03", "Huck[a-zA-Z]+|Saw[a-zA-Z]+" },
    { "twain_04a", "\\b\\w+nn\\b" },
    { "twain_04b", "\\bF\\w+n\\b" },
    { "twain_05", "[a-q][^u-z]{13}x" },
    { "twain_06", "Tom|Sawyer|Huckleberry|Finn" },
    { "twain_07", "(?i)Tom|Sawyer|Huckleberry|Finn" },
    { "twain_08", ".{0,2}(Tom|Sawyer|Huckleberry|Finn)" },
    { "twain_09", ".{2,4}(Tom|Sawyer|Huckleberry|Finn)" },
    { "twain_10", "Tom.{10,25}river|river.{10,25}Tom" },
    { "twain_11", "[a-zA-Z]+ing" },
    { "twain_12", "\\s[a-zA-Z]{0,12}ing\\s" },
    { "twain_13", "([A-Za-z]awyer|[A-Za-z]inn)\\s" },
    { "twain_14", "[\"'][^\"']{0,30}[?!\\.][\"']" },
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
        long end = ns();
        time += end - start;
    }

    return time / ITERS;
}

int main()
{
    std::FILE *fp = std::fopen("pg3200.txt", "r");
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

    for (int i = 0; i < NUM_BENCHES; i++) {
        uint64_t time = run_bench(contents, BENCHES[i].re);
        printf("test %s\t... bench:\t%'ld ns/iter (+/- 0) = %d MB/s\n",
                BENCHES[i].name, time, size * (1000 * 1000 * 1000 / 1024 / 1024) / time);
    }
}

