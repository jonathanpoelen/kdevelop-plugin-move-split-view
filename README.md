# kdevelop-move-split-view

Move and clean split views.

## Features

- Move the current file in the next/previous split view. Vertical split if only one view.
- Remove duplicate files in the current split view or between split views.

## Dependencies

- `cmake`
- `extra-cmake-modules`
- `gettext`
- `kdelibs5-dev` or `kdelibs5-devel`
<!-- - kdevplatform-dev -->

```
sudo apt install cmake extra-cmake-modules gettext kdelibs5-dev
```

## Install

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

Note: It may be necessary to add `-DPLUGIN_INSTALL_DIR=${your_path}` with `cmake`. For example `/usr/lib/qt/plugins/` or `/usr/lib/x86_64-linux-gnu/qt5/plugins/`.
