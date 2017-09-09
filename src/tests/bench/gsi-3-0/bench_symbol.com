$ ! define gsibench to start the extension
$ bench_symbol = f$parse("[]",,,,)
$ bench_symbol = f$extract(0, f$length(bench_symbol) - 2, bench_symbol)
$ gsibench :== $ 'bench_symbol'BENCH