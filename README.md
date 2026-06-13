# libcspd

Collection of utilities used to write C programs quickly and efficiently.

The purpose of the utilities are to provide a simple interface for leveraging common data structures. Here is a simple example of basic array usage via the `cspd_vector.h` interface.

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

##### Visual Studio

Note: Visual Studio Build Tools can be used for development if using a text editor, but the Visual Studio Community IDE is useful for debugging.

Use the Visual Studio (GUI) Installer to install the **Workloads** and **Individual components**.
- Workloads
  - Desktop Development for C++
- Individual components
  - C++ Clang Compiler for Windows (>=17.0.3)

Note: The **Individual components** are optional for the LSP configuration if using a text editor for development. The development environment for text editors can be configured simply by defining the MSVC environment using the provided Windows batch script.

For example, set the `Platform` variable to either `x86` for 32-bit targets or `x64` for 64-bit targets, and run the `devenv.bat` batch script to configure the MSVC environment.

```commandline
set Platform=x64
tools\devenv.bat
```

If a full IDE is desired, install Visual Studio Community.

```commandline
winget install --id=Microsoft.VisualStudio.2026.Community -e 
```

Otherwise, install Visual Studio Build Tools instead.

```commandline
winget install --id=Microsoft.VisualStudio.2026.BuildTools -e 
```

### Linux

The LLVM Clang compiler toolchain is used to build the project on Linux. The minimum Clang version tested is 17.0.6, though any newer version should work.

#### Dependencies

The LLVM Clang compiler toolchain is used as the LSP and for compiling the project on Linux.

```bash
sudo apt-get install clang
curl -O https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
tar -xf ./clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz
cd clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/bin/
./clang
sudo cp -R clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04/* /usr/
```

## Building

Instructions on how to build the project for use on both Windows and Linux.

### Linux

Clone the repository and build the project using `make`.

```bash
git clone https://github.com/cyn1x/libcspd.git
cd libcspd/
make
```

The `makefile` is in the project root directory.

### Windows

Clone the repository and build the project using the provided Windows batch file.

```commandline
git clone https://github.com/cyn1x/libcspd.git
cd libcspd
tools\build.bat
```

The build script attempts to locate the Visual Studio install directory, but this can be specified manually to override this behaviour.
1. Create a file named `env.ini` in the project root directory
2. Assign the absolute path of `vcvarsall.bat` as the *value* to the `MsvcDir` *key*.

Example showing how to add a non-standard program install location of `C:\Apps` for Visual Studio Community 2022.

```ini
MsvcDir="C:\Apps\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
```

Clone the repository and run the build script to create the DLL and LIB files.

## Usage

For use in other projects, both build scripts show an example of how to link the library to another program. The test program in the `bin` directory does exactly this.

### Windows

Running the resulting test program executable in the build output directory on Windows.

```commandline
cd libcspd
bin\win32\Debug_x64\libcspd_x64.exe
```

The `makefile` build target will output a Shared Object file `libcspd.so` for dynamically linking in other programs. In the example below, the included program used for testing imports the library for testing purposes.

### Linux

Running the resulting test program binary in the build output directory on Linux.

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
tools\doc.sh
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
- [x] Memory Allocator Plugin
