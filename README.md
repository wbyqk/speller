# speller

A student-friendly variant of CS50's Pset5 speller configured for cross-platform builds (Windows, Linux, macOS) using CMake.

## Build

Using CMake (recommended):

```sh
# from the speller directory
cmake -S . -B build
cmake --build build --config Release
```

The resulting executable will be at `build/speller` (or `build/Release/speller.exe` on Windows with MSVC).

If you prefer Make (on Unix-like systems only), a legacy `Makefile` is included, but CMake is recommended for Windows compatibility.

## Run

```sh
# default dictionary
./build/speller texts/lalaland.txt

# specify dictionary
./build/speller dictionaries/small texts/cat.txt
```

## Notes for students
- `dictionary.c` contains TODOs for you to implement: `load`, `check`, `hash`, `size`, and `unload`.
- Timing uses standard C `clock()` for portability (no `sys/resource.h`).
- Keep your implementation within the provided API in `dictionary.h`.
