# Route20

Cross-Platform C++ Dataflow Metaprogramming Framework

Route20 is a powerful C++ dataflow metaprogramming library that allows you to create and route complex dataflow systems at compile-time.

## Build & Run

_**NOTE:** A C++20 compatible compiler is required to build this project._

```
git clone https://github.com/cross-platform/route20.git
cd route20
mkdir build
cd build
cmake ..
make

./example/route20-example
```

- *`cmake ..` will auto-detect your IDE / compiler. To manually select one, use `cmake -G`.*
- *When building for an IDE, instead of `make`, simply open the cmake generated project file.*

The source code for the `route20-example` application above can be found in the "example" folder.
