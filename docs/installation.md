# Installation

## Pre-requirements

Install Git client, CMake, GCC/Clang compiler and Qt5 development packages from your distro's repositories.

## Versions

You need the following versions:

  * GCC: 7.4+;
  * Clang: 7.0+;
  * CMake: 3.10+;
  * Qt 5.7+.

## Downloading sources

Download sources using Git:

```
git clone --depth=1 --recursive https://github.com/EasyCoding/tuned-switcher.git tuned-switcher
```

You can also use [release tarballs](https://github.com/EasyCoding/tuned-switcher/releases).

## Building from sources

Run build:

```
cd tuned-switcher
mkdir build
cd build
cmake ..
cmake --build .
```

## Installing binaries

Install result:

```
cd tuned-switcher/build
sudo make install
```
