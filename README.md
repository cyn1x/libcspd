# libcspd

![License](https://img.shields.io/github/license/cyn1x/libcspd)
![Language](https://img.shields.io/badge/language-C-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey)

A cross-platform C library providing core data structures and utilities for efficient C program development. The purpose of these utilities is to provide a simple interface for leveraging common data structures when programming in C.

```c
#include "cspd_print.h"
#include "cspd_vector.h"

/** 
 * Simple program demonstrating one of many utilities available.
 */
int main(int argc, char *argv[])
{
    // Create a vector to store a contiguous array of elements
    vector_t vec;
    cspd_vector_init(&vec, sizeof(int32));

    // Create 10 elements and push them into the vector
    for (int32 i = 0; i < 10; ++i) {
        int32 k = i;
        cspd_vector_push(&vec, &k);
    }

    cspd_print_vector(int32, &vec);
    // Output: { 0 1 2 3 4 5 6 7 8 9 }

    // Insert data into the vector
    int32 data[] = {10, 11, 12};
    cspd_vector_insert(&vec, 4, sizeof(data), &data);

    cspd_print_vector(int32, &vec);
    // Output: { 0 1 2 3 10 11 12 4 5 6 7 8 9 }

    return 0;
}
```

There is also support for integrating custom memory allocators via the `cspd_mem.h` interface. The default behaviour uses the `stdlib.h` memory functions.

## Background

This project started as a way to learn data structures and algorithms from the ground up, and grew into a set of tools I now use in my own pet projects. It's published here as a reference and source of inspiration for anyone building their own utility library or learning how common data structures are implemented in C.

Contributions, bug reports, and forks are welcome.

## Installation

This program can be compiled on both Windows and Linux by cloning the repository and running the respective build scripts after installing the required dependencies.

ℹ️ Currently only supports x86 and x64 architectures.

### Windows

MSVC is used to build the project on Windows, and Doxygen is used to generate documentation.

#### Dependencies

- Microsoft Visual Studio Community (>= 2022) or Build Tools (>= 2022)
- Doxygen

<details>
<summary>Installing Visual Studio</summary>

Microsoft Visual Studio Build Tools can be used to compile the project library DLL as an alternative to a full IDE installation.

Use the Visual Studio Installer (GUI) to install the **Workloads** and **Individual components**.
- Workloads
  - Desktop Development for C++
- Individual components
  - C++ Clang Compiler for Windows (>=17.0.3)

Note: The **Individual components** are optional for the LSP configuration if using a text editor for development. If a full IDE is desired, install Visual Studio Community.

```commandline
winget install --id=Microsoft.VisualStudio.2026.Community -e 
```

Otherwise, install Visual Studio Build Tools instead.

```commandline
winget install --id=Microsoft.VisualStudio.2026.BuildTools -e 
```

</details>

### Linux

The LLVM Clang compiler toolchain is used to build the project on Linux. The minimum Clang version tested is 17.0.6, though any newer version should work.

#### Dependencies

```bash
sudo apt-get install clang
```

<details>
<summary>Installing a specific Clang version manually</summary>

```bash
curl -O https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
tar -xf ./clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
cd clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/bin/
./clang
sudo cp -R clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/* /usr/
```

</details>

## Building

### Linux

```bash
git clone https://github.com/cyn1x/libcspd.git
cd libcspd/
make
```

### Windows

```commandline
git clone https://github.com/cyn1x/libcspd.git
cd libcspd
tools\build.bat
```

The build script attempts to locate the Visual Studio install directory automatically. To override this, create a file named `env.ini` in the project root and set the path to `vcvarsall.bat`:

```ini
MsvcDir="C:\Apps\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
```

## Usage

For use in other projects, both the Windows and Linux build scripts show an example of how to link the library to another program. The test program in the `bin` directory does exactly this.

## Development

The project is currently being developed using [Neovim](https://github.com/neovim/neovim). There is no strict development environment enforced.

### Windows

Run the `devenv.bat` batch script to configure the MSVC environment. The platform will be automatically detected (`x86` for 32-bit, `x64` for 64-bit).

If using Visual Studio Community, open `libcspd.sln` and press F11 to start debugging.

### Linux

Ensure Clang is available on the system PATH.

## Tests

### Windows

```commandline
cd libcspd
bin\win32\Debug_x64\libcspd_x64.exe
```

### Linux

```bash
cd libcspd/
LD_LIBRARY_PATH="/absolute/path/to/libcspd/lib/linux/Debug_x64;$LD_LIBRARY_PATH" ./bin/linux/Debug_x64/libcspd
```

Memory leaks can be checked with Valgrind:

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
tools\doc.sh
```

## Roadmap

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
- [x] Memory Allocator Plugin
