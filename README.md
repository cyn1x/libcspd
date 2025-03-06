# libcspd

Collection of utilities used to write C programs quickly and efficiently.

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
