Benchmarking
============

c0ban Core has an internal benchmarking framework, with benchmarks
for cryptographic algorithms such as SHA1, SHA256, SHA512 and RIPEMD160. As well as the rolling bloom filter.

After compiling c0ban-core, the benchmarks can be run with:
`src/bench/bench_c0ban`

The output will look similar to:
```
#Benchmark,count,min,max,average
Base58CheckEncode,524288,0.000025475927487,0.000025475927487,0.000025475927487
Base58Decode,655360,0.000000859894499,0.000001886512109,0.000001771632378
Base58Encode,524288,0.000001011663699,0.000002229033271,0.000002087913344
RIPEMD160,512,0.024737918283790,0.024737918283790,0.024737918283790
RollingBloom-refresh,1,0.000131000000000,0.000131000000000,0.000131000000000
RollingBloom-refresh,1,0.000094000000000,0.000094000000000,0.000094000000000
RollingBloom-refresh,1,0.000112000000000,0.000112000000000,0.000112000000000
RollingBloom-refresh,1,0.000099000000000,0.000099000000000,0.000099000000000
RollingBloom-refresh,1,0.000159000000000,0.000159000000000,0.000159000000000
RollingBloom-refresh,1,0.000094000000000,0.000094000000000,0.000094000000000
RollingBloom-refresh,1,0.000094000000000,0.000094000000000,0.000094000000000
RollingBloom-refresh,1,0.000103000000000,0.000103000000000,0.000103000000000
RollingBloom-refresh,1,0.000212000000000,0.000212000000000,0.000212000000000

```

More benchmarks are needed for, in no particular order:
- Script Validation
- CCoinDBView caching
- Coins database
- Memory pool
- Wallet coin selection
