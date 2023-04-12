# Generic installation

## Pre-requirements

Install Git client, CMake, GCC/Clang compiler and Qt5 development packages from your distro's repositories.

## Versions

You need the following versions:

  * GCC: 7.4+;
  * Clang: 7.0+;
  * CMake: 3.12+;
  * Qt 6.2 or 5.15;
  * doxygen (for building documentation);
  * pandoc (for generating manpage).

## Downloading sources

Download sources using Git:

```
git clone --depth=1 https://github.com/xvitaly/tuned-switcher.git tuned-switcher
```

You can also use [release tarballs](https://github.com/xvitaly/tuned-switcher/releases).

## Building from sources

Run build:

```
cmake -S tuned-switcher -B tuned-switcher/build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build tuned-switcher/build
```

## Installing binaries

Install result:

```
sudo cmake --install tuned-switcher/build
```
