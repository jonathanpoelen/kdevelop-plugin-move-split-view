# kdevelop-move-split-view

Move and clean split views.

## Features

- Move the current file in the next/previous split view. Vertical split if only one view.
- Remove duplicate files in the current split view or between split views.

## Dependencies

- cmake
- cmake-extras
- kdelibs5-dev or kdelibs5-devel
- kdevplatform-dev
- clang++ or g++ with c++14 support

```
sudo apt install cmake cmake-extras kdelibs5-dev kdevplatform-dev
```

## Install

### KDevelop5

```
mkdir build
cd build
cmake -DPLUGIN_INSTALL_DIR=/usr/lib/x86_64-linux-gnu/qt5/plugins/ -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

### KDevelop4

https://github.com/jonathanpoelen/kdevelop-plugin-move-split-view/releases/tag/kdev4-v0.7
