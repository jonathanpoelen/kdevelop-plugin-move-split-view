# kdevelop-move-split-view

Move and clean split views.

## Features

- Move the current file in the next/previous split view. Vertical split if only one view.
- Remove duplicate files in the current split view or between split views.

## Dependencies

- `cmake`
- `extra-cmake-modules`
- `gettext`
- `kdelibs6-dev` or `kdelibs6-devel`
<!-- - kdevplatform-dev -->

```
sudo apt install cmake extra-cmake-modules gettext kdelibs5-dev
```

## Install

```
cmake -DQT_MAJOR_VERSION=6 -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build
sudo cmake --build build install
```

Note: It may be necessary to add `-DPLUGIN_INSTALL_DIR=${your_path}` with `cmake`. For example `/usr/lib/qt6/plugins/` or `/usr/lib/x86_64-linux-gnu/qt6/plugins/`.
