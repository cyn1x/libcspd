# libcspd

Collection of utilities used to write C programs quickly and efficiently.

The purpose of the utilities are to teach data structures and algorithms, as well as provide a simple interface for leveraging common data structures. Here is a simple example of what this means.

```c
#include "print.h"
#include "vector.h"

/** 
 * Simple program demonstrating one of many utilities available.
 */
int main(int argc, char *argv[])
{
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

This program can be compiled on both Windows and Linux by cloning the repository and running the respective build scripts after installing the required dependencies.

Supports both 32-bit and 64-bit platforms.

### Windows

MSVC is used to build the project on Windows, and Doxygen is used to generate documentation.

#### Dependencies
Microsoft Visual Studio Build Tools can be used to compile the project library DLL as an alternative to a full IDE installation.

- Microsoft Visual Studio 
  - Community (>= 2022) or Build Tools (>= 2022)
- Doxygen

Use the Visual Studio (GUI) Installer to install the **Workloads** and **Individual components**.
- Workloads
  - Desktop Development for C++
- Individual components
  - MSBuild support for LLVM (clang-cl) toolset
  - C++ Clang Compiler for Windows (>=17.0.3)

Installing the development environment.

```commandline
winget install --id=Microsoft.VisualStudio.2026.Community -e 
```

If the full IDE install is not required, install Build Tools instead.

```commandline
winget install --id=Microsoft.VisualStudio.2026.BuildTools -e 
```

Clone the repository and run the build script to create the DLL and LIB files.

```commandline
git clone https://github.com/cyn1x/libcspd.git
cd libcspd
tools\build.bat
```

Note that Visual Studio Build Tools can be used for development if using a text editor, but the Visual Studio IDE is useful for debugging.

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
bin\win32\Debug_x64\libcspd_x64.exe
```

The `makefile` build target will output a Shared Object file `libcspd.so` for dynamically linking in other programs. In the example below, the included program used for testing imports the library for testing purposes.

### Linux
```bash
cd libcspd/
LD_LIBRARY_PATH="/absolute/path/to/libcspd/lib/linux/Debug_x64;$LD_LIBRARY_PATH" ./bin/linux/Debug_x64/libcspd
```

Memory leaks can be checked with Valgrind by also dynamically linking the library to another program.

```bash
LD_LIBRARY_PATH="/absolute/path/to/libcspd/lib/linux/Debug_x64;$LD_LIBRARY_PATH" valgrind --leak-check=yes ./bin/linux/Debug_x64/libcspd
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

Legend:

&#x2705; done &nbsp;|&nbsp; &#x1F504; in progress &nbsp;|&nbsp; &#x23F3; planned

Current features:

- &#x2705; Vector
- &#x2705; Linked List
- &#x2705; Stack
- &#x2705; Queue
- &#x2705; Binary Tree

Future Plans:

- &#x1F504; Binary Search Tree
- &#x1F504; Hash map
- &#x1F504; Heap
- &#x23F3; B-tree
- &#x23F3; R-tree
- &#x23F3; AVL Tree

Housekeeping: 

- [ ] Benchmarks
- [ ] Basic demo application
- [ ] Host Doxygen documentation online
- [ ] C++ wrappers for incompatible C functions
