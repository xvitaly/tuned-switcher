%undefine __cmake_in_source_build

Name: tuned-switcher
Version: 0.2.0
Release: 1%{?dist}

# Main code - GPLv3+.
# Icon - Apache 2.0.
License: GPLv3+ and ASL 2.0
Summary: Simple utility to manipulate the Tuned service
URL: https://github.com/EasyCoding/%{name}
Source0: %{url}/archive/v%{version}/%{name}-%{version}.tar.gz

BuildRequires: cmake(Qt5Core)
BuildRequires: cmake(Qt5DBus)
BuildRequires: cmake(Qt5Gui)
BuildRequires: cmake(Qt5LinguistTools)
BuildRequires: cmake(Qt5Widgets)

BuildRequires: cmake
BuildRequires: desktop-file-utils
BuildRequires: gcc-c++
BuildRequires: libappstream-glib
BuildRequires: ninja-build

Requires: hicolor-icon-theme
Requires: tuned

%description
Tuned Switcher is a simple utility to manipulate the Tuned service.

%prep
%autosetup -p1

%build
%cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_APPLET:BOOL=ON \
    -DBUILD_DOCS:BOOL=OFF \
    -DBUILD_GUI:BOOL=ON
%cmake_build

%check
appstream-util validate-relax --nonet %{buildroot}%{_datadir}/metainfo/*.metainfo.xml
desktop-file-validate %{buildroot}%{_datadir}/applications/*.desktop

%install
%cmake_install
%find_lang %{name} --with-qt

%files -f %{name}.lang
%doc README.md
%license COPYING
%{_bindir}/%{name}*
%{_datadir}/applications/*.desktop
%{_datadir}/icons/hicolor/*/apps/*.*
%{_metainfodir}/*.metainfo.xml

%changelog
* Mon Mar 15 2021 Vitaly Zaitsev <vitaly@easycoding.org> - 0.2.0-1
- Updated to version 0.2.0.

* Thu Mar 04 2021 Vitaly Zaitsev <vitaly@easycoding.org> - 0.1.0-1
- Initial SPEC release.
