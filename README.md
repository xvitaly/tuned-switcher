# Tuned Switcher

[![GitHub version](https://img.shields.io/github/v/release/EasyCoding/tuned-switcher?sort=semver&color=brightgreen&logo=git&logoColor=white)](https://github.com/EasyCoding/tuned-switcher/releases)
[![GCC CI status](https://github.com/EasyCoding/tuned-switcher/actions/workflows/gcc.yml/badge.svg)](https://github.com/EasyCoding/tuned-switcher/actions/workflows/gcc.yml)
[![Clang CI status](https://github.com/EasyCoding/tuned-switcher/actions/workflows/clang.yml/badge.svg)](https://github.com/EasyCoding/tuned-switcher/actions/workflows/clang.yml)
[![Flatpak CI status](https://github.com/EasyCoding/tuned-switcher/actions/workflows/flatpak.yml/badge.svg)](https://github.com/EasyCoding/tuned-switcher/actions/workflows/flatpak.yml)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/EasyCoding/tuned-switcher.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/EasyCoding/tuned-switcher/context:cpp)
[![LGTM alerts](https://img.shields.io/lgtm/alerts/g/EasyCoding/tuned-switcher.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/EasyCoding/tuned-switcher/alerts/)
[![CodeFactor](https://www.codefactor.io/repository/github/easycoding/tuned-switcher/badge)](https://www.codefactor.io/repository/github/easycoding/tuned-switcher)
[![Codacy](https://app.codacy.com/project/badge/Grade/aa1c30566f9244b8a677a775d1672604)](https://www.codacy.com/gh/EasyCoding/tuned-switcher/dashboard)
[![GitHub issues](https://img.shields.io/github/issues/EasyCoding/tuned-switcher.svg?label=issues)](https://github.com/EasyCoding/tuned-switcher/issues)
---

## About

Tuned Switcher is a simple utility for managing performance profiles using the [Tuned service](https://github.com/redhat-performance/tuned).

Tuned is a daemon for monitoring and adaptive tuning of system devices. In order to use this program, a daemon must be installed on your system.

## Downloads

<a href="https://flathub.org/apps/details/org.easycoding.TunedSwitcher"><img width="240" height="80" alt="Download on Flathub" src="https://flathub.org/assets/badges/flathub-badge-en.svg"></img></a>
<a href="https://snapcraft.io/tuned-switcher"><img width="240" height="80" alt="Get it from the Snap Store" src="https://snapcraft.io/static/images/badges/en/snap-store-black.svg"></img></a>

## Screenhots

Screenhots are available [here](docs/screenshots.md).

## Features

Supported features:

  * shows the currently selected profile;
  * easy and simple switching of performance profiles;
  * automatic mode support;
  * profile switch notifications;
  * optional widget-only mode support.

## Modes

This program can operate in two modes:

  * system tray icon (aka applet) - default and recommended mode with support of all available features;
  * GUI application (aka widget) - simplified mode with some features are not available.

If current desktop environment has a system tray support, an applet will be used, otherwise a widget.

## License

Licensed under the terms of the GNU General Public License version 3. You can find it here: [LICENSE](LICENSE).

Icon from the [Noto Emoji](https://github.com/googlefonts/noto-emoji) font, licensed under the terms of the [Apache License 2.0](licenses/noto-emoji.LICENSE.txt).

## Documentation

Documentation is available [here](docs/README.md).
