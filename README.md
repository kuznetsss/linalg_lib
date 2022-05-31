# linalg_lib

Linalg is a linear algebra library designed to run with real-time constraints.


## Build from source

The library itself is header only so only tests are needed to be compiled.

### Requirements

Requirements to build linalg from source are:
- C++ compiler clang 13.0.1 or higher (gcc also could be used see (below)[### Cmake options])
- C++ linker lld 13.0.1 or higher (any other linker also could be used see (below)[### Cmake options])
- CMake (tested with 3.23.1)

### CMake options

The next CMake options could be customized:
- `CMAKE_CXX_COMPILER` - full path to compiler
- `CMAKE_EXE_LINKER_FLAGS` - linker flags (e.g. to choose linker use `-fuse-ld=<linker_name>`)

### Build types

The next build types are defined:
- `Debug` - no optimization, full debug info
- `Release` - maximum optimizations, no assertions
- `Release-lto` - like `Release` but with link time optimization enabled
- `Msan` - small optimizations, memory sanitizer, no assertions
- `Msan` - small optimizations, address sanitizer, no assertions

### Build

To build all tests use commands:
```
$ cmake -DCMAKE_BUILD_TYPE=<build_type> -B <build_dir>
$ cmake --build <build_dir>
```

### Running tests

There are two tests awaliable:
- Unit tests checking all classes.
To run use:
```
$ ./build/tests/unit/unit_tests
```

- Integration test checking solving a system of linear equations.
To run use:
```
$ ./build/tests/integration/test_from_example/run_test.sh
```


## Usage

To use linalg in your project only `include/` directory is needed (There is an issue to make releases #3).

### Features
Features of the library are:
- Operations with matrices and vectors : inversion, transposition, multiplication
- Optimized `inverse()` operations calculates inversed matrix only explicitly
- Compile-time calculations: all operations are `constexpr`
- No exceptions (except `Debug` build type): all operations are marked as `noexcept`
- Assertions in `Debug` build type

### Limitations and disadvantages

The library has some limitations:
- All matrices and vectors data is stored on stack. It may cause stack overflow. Custom allocators could help here (see #13)
- Matrices and vectors are not initialized by default. An assertion will fail on access to uninitialized field only in `Debug` build
- Some algorithms could be optimized to use CPU cache more effectively
- `operator,()` in objects initialization ignores redundant so it's easy to make a mistake

### Example of usage

[Integration test](https://github.com/kuznetsss/linalg_lib/tree/main/tests/integration) is a good example of how to use the library.

## CI

CI has some automated checks using Github workflows:
- Clang-tidy checks
- Build and run all tests for all awaliable build types

Notifications about failed workflows are sent to my Telegram.


## Credits

Thanks to Timur Doumler for the really helpful [talk](https://www.youtube.com/watch?v=Tof5pRedskI) about using C++ for real-time applications.


