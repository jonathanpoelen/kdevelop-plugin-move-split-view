kdevelop-plugin-view-switcher
=============================

Move and remove split views.

Features
--------

 - Move the current file in the following split view
 - Move the current file in the previous split view
 - Delete the views already present in other split views
 - Delete the views found in other split views
 - Moving a file from one split view to the other. Split if it is not already.

Dependencies
------------

Debian and derived
 - kdelibs5-dev

Other distros
 - kdelibs5-devel

Install
-------

### KdevPlatform 14 (Kdevelop 4.4)

```sh
sed -i 's/X\-KDevelop\-Version=[0-9][0-9]/X-KDevelop-Version=14/' kdevswitchviewer.desktop
```

### KdevPlatform 15 (Kdevelop 4.5)

```sh
sed -i 's/X\-KDevelop\-Version=[0-9][0-9]/X-KDevelop-Version=15/' kdevswitchviewer.desktop
```

### All versions

As a user

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$(kde4-config --localprefix) -DQT_QMAKE_EXECUTABLE=/usr/bin/qmake-qt4
make
make install
```

or

As root user

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$(kde4-config --prefix) -DQT_QMAKE_EXECUTABLE=/usr/bin/qmake-qt4
make
sudo make install
```

Old repository
--------------

https://code.google.com/p/kdevelop-plugin-view-switcher/source/browse/#svn%2Ftrunk%2Ftag-1%253Fstate%253Dclosed
