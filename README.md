# libcspd

Collection of utilities used to write C programs quickly and efficiently.

The purpose of the utilities are to teach data structures and algorithms, as well as provide a simple interface for leveraging common data structures. Here is a simple example of what this means.

```c
#include "print.h"
#include "vector.h"
#include <log.h>

int main(int argc, char *argv[])
{
    // Simple program demonstrating the usage of one of the many utilities 
    // available in the libcspd library
    
    log_init(LOG_TRACE, stdout, NULL);

    // Create a vector to store a contiguous array of elements
    vector_t vec;
    vector_init(&vec, sizeof(int32));

    // Create 10 elements and push them into the vector
    for (int32 i = 0; i < 10; ++i) {
        int32 k = i;
        vector_push(&vec, &k);
    }

    print_vector(int32, &vec);
    // Output: { 0 1 2 3 4 5 6 7 8 9 }

    // Insert data into the vector
    int32 data[] = {10, 11, 12};
    vector_insert(&vec, 4, sizeof(data), &data);

    print_vector(int32, &vec);
    // Output: { 0 1 2 3 10 11 12 4 5 6 7 8 9 }

    return 0;
}
```

## Installation

This program can be installed on both Windows and Linux by cloning the repository and running the respective build scripts after installing the required dependencies.

### Windows

MSVC is used to build the project on Windows.

#### Dependencies

Ensure Desktop Development for C++ is selected under the **Workloads** tab, and C++ Clang Compiler for Windows (17.0.3) is selected under **Individual components** tab. Newer versions of Clang should work also.

- Microsoft Visual Studio 2022
  - Desktop Development for C++
  - C++ Clang Compiler for Windows (17.0.3)
- Microsoft Visual Studio 2022 Build Tools
- Doxygen

```commandline
winget install --id=Microsoft.VisualStudio.2022.Community -e && winget install --id=Microsoft.VisualStudio.2022.BuildTools -e 
git clone https://github.com/cyn1x/libcspd.git
cd libcspd
tools\build.bat
```

### Linux

Clang is used to build the project on Linux. The Clang version used is 17.0.6 though should work with any newer version.

```bash
sudo apt-get install clang
curl -O https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
tar -xf ./clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
cd clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/bin/
./clang
sudo cp -R clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/* /usr/
git clone https://github.com/cyn1x/libcspd.git
cd libcspd/
```

Finally, run the respective build scripts to compile. 
### Windows
```commandline
cd libcspd
tools\build.bat
```

### Linux
```bash
cd libcspd/
make
```

## Usage

Instructions on how to compile and link the program for development on the project. For use in other projects, both build scripts show an example of how to link the library to another program. The program under the `tests` directory does exactly this.

### Windows
```commandline
cd libcspd
tests\bin\libcspd.exe
```

The `makefile` build target will output a Shared Object file `libcspd.so` for dynamically linking in other programs. In the example below, the included program used for testing imports the library for testing purposes.

### Linux
```bash
cd libcspd/
LD_LIBRARY_PATH="/absolute/path/to/libcspd/bin;$LD_LIBRARY_PATH" ./tests/bin/libcspd
```

Memory leaks can be checked with Valgrind by also dynamically linking the library to another program.

```bash
LD_LIBRARY_PATH="/mnt/d/Dev/GitHub/cyn1x/libcspd/bin;$LD_LIBRARY_PATH" valgrind --leak-check=yes ./tests/bin/libcspd 
```

## Documentation

Doxygen is used to generate documentation. The resulting website will be generated in the `/doc` directory.

### Windows
```
tools\doc.bat
```

### Linux
```

```

## Roadmap

The following serves as a rough outline of what features will be implemented.

Data structures and algorithms
- [x] Vector
- [x] Linked List
- [x] Stack
- [x] Queue
- [x] Binary Tree
- [ ] Binary Search Tree
- [ ] Hash map
- [ ] Heap
- [ ] B-tree
- [ ] R-tree
- [ ] AVL Tree

Performance
- [ ] Performance profiling
- [ ] Optimised versions of algorithms

GUI
- [ ] UI for visualising algorithms

Housekeeping
- [ ] Basic demo application
- [ ] Host Doxygen documentation online
