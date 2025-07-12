#include <benchmark/benchmark.h>

struct Bitfields
{
    void a(unsigned n) { a_ = n; }
    void b(unsigned n) { b_ = n; }
    void c(unsigned n) { c_ = n; }
    void d(unsigned n) { d_ = n; }
    unsigned a() const { return a_; }
    unsigned b() const { return b_; }
    unsigned c() const { return c_; }
    unsigned d() const { return d_; }
    volatile unsigned a_:1,
                      b_:5,
                      c_:2,
                      d_:8;
};

struct SeparateFields
{
    void a(unsigned n) { a_ = n; }
    void b(unsigned n) { b_ = n; }
    void c(unsigned n) { c_ = n; }
    void d(unsigned n) { d_ = n; }
    unsigned a() const { return a_; }
    unsigned b() const { return b_; }
    unsigned c() const { return c_; }
    unsigned d() const { return d_; }
    volatile unsigned a_, b_, c_, d_;
};

struct ExplicitBitOperations
{
    void a(unsigned n) { x_ &= ~0x01; x_ |= n; }
    void b(unsigned n) { x_ &= ~0x3E; x_ |= n << 1; }
    void c(unsigned n) { x_ &= ~0xC0; x_ |= n << 6; }
    void d(unsigned n) { x_ &= ~0xFF00; x_ |= n << 8; }
    unsigned a() const { return x_ & 0x01; }
    unsigned b() const { return (x_ & 0x3E) >> 1; }
    unsigned c() const { return (x_ & 0xC0) >> 6; }
    unsigned d() const { return (x_ & 0xFF00) >> 8; }
    volatile unsigned x_ = 0;
};

template <typename T>
static void BM_Struct(benchmark::State& state)
{
    for (auto _ : state)
    {
        int n = 0;
        T t;
        for (int i = 0; i < 10000000; ++i)
        {
            t.a(i & 0x01);
            t.b(i & 0x1F);
            t.c(i & 0x03);
            t.d(i & 0xFF);
            n += t.a() + t.b() + t.c() + t.d();
        }
        benchmark::DoNotOptimize(n);
    }
}

BENCHMARK_TEMPLATE(BM_Struct, Bitfields)->Repetitions(5)->ReportAggregatesOnly(true)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_Struct, SeparateFields)->Repetitions(5)->ReportAggregatesOnly(true)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_Struct, ExplicitBitOperations)->Repetitions(5)->ReportAggregatesOnly(true)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
