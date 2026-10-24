# Airline Route Records Manager

An individual C coursework project that loads route/passenger records from a simple comma-delimited input file, consolidates repeated origin/destination/airline tuples across six months, and supports interactive searches by route, origin, destination, or airline. The owner confirms they wrote the substantive implementation. The archived source files match this release copy; no separate assignment prompt or instructor source file was located in the reviewed project records.

## Technologies and concepts

- C structs, pointers, dynamic allocation, file I/O, and a Makefile
- Route-key lookup, aggregation, recursion, and interactive menu input
- Standard C library only; no third-party code or data is bundled

## Repository layout

- `src/main.c` — command-line entry point and search menu
- `src/route-records.c`, `src/route-records.h` — record parsing, allocation, aggregation, and searches
- `src/Makefile` — GCC build recipe; target output is `airline`

## Build and use

From `src/`, run `make`, then run `./airline path/to/route-records.csv`. The expected input is a header row followed by simple comma-separated route fields and monthly passenger counts. No dataset is included; use only a separately sourced input file. Run `make clean` to remove local object files and the executable.

## Attribution and starter-material review

The owner confirms this was an individual assignment and that they authored the substantive implementation. The reviewed archive contained the project source and an interview guide, but no assignment handout or separate instructor starter file. The candidate source contains ordinary C includes, project function prototypes, and standard boilerplate; no marked instructor-authored implementation block or license notice was identified. The owner recalls starter/template use in coursework generally, but no specific instructor-provided block was identifiable in these files. This description does not claim that every line was independently written. No license is included.

## Limitations

The parser handles only simple comma-separated fields, not full CSV quoting. `%[^,]` scans have no width limits for 4-byte code fields, month indices are not range-checked, and recursive linear lookup can make aggregation quadratic in the number of unique routes. The menu's “Average Passengers per Month” result is total passengers divided by match count, not by six months. Do not use on untrusted input. The source has not been built or tested as part of this review. It performs file-based/in-memory processing; it does not use a SQL database.
