# Installation

## Pre-requirements

Install the Git client, CMake, GCC/Clang compiler with standard library, and Qt6 development packages from your distribution's repositories.

## Versions

You need the following versions:

  * C++20 capable compiler: GCC 13+ or Clang 16+;
  * CMake: 3.28+;
  * Qt 6.2+;
  * doxygen (for building documentation);
  * pandoc (for generating manpage).

## Configuration options

This project supports the following build-time configuration options, which can be enabled or disabled using `-DOPTION_NAME=ON/OFF`:

| Name | Description | Default |
| ------- | ------- | ------- |
| BUILD_DOC | Build and install API and application documentation in HTML format. | OFF |
| BUILD_MANPAGE | Build and install manpage with documentation. | OFF |
| BUILD_TESTS | Build various tests. | OFF |
| LINK_ALL_STATICALLY | Link the program against all libraries statically (no dependencies mode). | OFF |
| LINK_ENABLE_OPTIMIZATIONS | Enable link-time optimizations if supported by current C++ compiler. | OFF |
| SYSTEMD_INTEGRATION | Enable systemd DBus API integration. | ON |

Any other non-default options related to external dependencies are not supported and should not be used.

## Downloading sources

Download sources using Git:

```
git clone --depth=1 https://github.com/xvitaly/tuned-switcher.git tuned-switcher
```

You can also use the [release tarballs](https://github.com/xvitaly/tuned-switcher/releases).

## Building from sources

Start the build process:

```
cmake -S tuned-switcher -B tuned-switcher/build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build tuned-switcher/build
```

## Installing binaries

Install the result:

```
sudo cmake --install tuned-switcher/build
```
