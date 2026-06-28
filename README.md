# RepCRec — Replicated Concurrency Control and Recovery

A distributed database simulator that keeps transactions correct and data consistent **even as individual sites fail and recover**.

## Why this exists

A single-machine database can lean on one consistent copy of the data. A distributed database can't: data is replicated across many sites, any of which can crash and later come back with stale state, all while transactions keep running. The hard part is guaranteeing that transactions still behave as if they ran one-at-a-time on a single correct copy. RepCRec is a from-scratch implementation of the mechanisms that make that possible — replication, concurrency control, deadlock handling, and failure recovery — so the behavior can be reasoned about and tested directly rather than treated as a black box.

## The model

- **10 sites**, **20 variables** (x1 … x20).
- Even-indexed variables are **replicated at all sites**; odd-indexed variable `xi` lives at the single site `1 + (i mod 10)`.
- A central **Transaction Manager** translates a stream of operations into reads and writes against the sites, decides where reads can be served, and enforces consistency.

## What it implements

- **Available-copies replication** — writes go to every up site holding the variable; reads are served from an available, up-to-date copy.
- **Concurrency control with serializable scheduling** — transactions are ordered so the result is equivalent to a serial execution.
- **Deadlock detection** — cycles in the waits-for graph are detected and broken by aborting the youngest transaction in the cycle.
- **Site failure & recovery** — a failed site loses its volatile state; on recovery, replicated variables are handled correctly (reads are restricted until a value is known good again), so consistency holds across failures.
- **Operation interface** — processes `begin`, `read`, `write`, `end`, `fail`, `recover`, and `dump` commands from an input script.

## Repository structure

```
main.cpp                  # entry point: drives the simulation from a test file
TransactionManager.cpp/.hpp   # routing, concurrency control, deadlock detection
transaction.cpp/.hpp      # transaction state and lifecycle
operation.cpp/.hpp        # parsing and representation of operations
site.cpp/.hpp             # per-site data, status, failure/recovery
makefile
tests/                    # 25 provided test cases + 5 additional custom cases
outputs/                  # captured outputs for the test cases
testCheck.sh              # runs ./main over every test in tests/
RepCRecV2.rpz             # ReproZip bundle for reproducible runs
```

## Building and running

Compiles on NYU CIMS with `gcc` 11.5.0.

```bash
make RepCRec               # builds the ./main executable
./main <testCase.txt>      # run a single test, e.g. ./main test1
```

To run the full suite, `testCheck.sh` executes `./main` over every file in `tests/` and writes results to `outputs/`. `RepCRecV2.rpz` is a ReproZip bundle capturing those runs for reproducibility.

## Tech stack

C++ · Make · ReproZip · NYU CIMS

## Authors

Final project for **Advanced Databases** at NYU, by **Jackson Oleson** and **Mihir Prajapati**.
