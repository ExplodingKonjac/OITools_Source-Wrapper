# OITools::Source-Wrapper

A program used to wrap source codes of contest into a tidy form.

This project is part of OITools Project.

This project is using [the Boost Library](https://www.boost.org/).

## How to use

Run `oit-wrap --help`.

## Build & Install

Requirements:

* GCC (MinGW in Windows)
* CMake
* Boost Library

You may need administrator privileges during the following steps.

### Linux

Run the following commands under the source directory:

```bash
cmake . -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install . --prefix=${install_directory}
```

where `${install_directory}` is the directory to install in. If `--prefix` is not specified, it'll be `/usr/local/`.

### Windows

Run the following commands under the source directory:

```bash
cmake . -DCMAKE_BUILD_TYPE=Release -G"MinGW Makefiles"
cmake --build .
cmake --install . --prefix=${install_directory}
```

where `${install_directory}` is the directory to install in. If `--prefix` is not specified, it'll be `C:/Program Files/OITools/`.
