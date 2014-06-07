kdevelop-plugin-view-switcher
=============================

To switch between the views of KDevelop (file splitter).

The transition from one view to another is done in a loop, view the following is the first and last one before the first one is the last.

Features
--------

 - Go to the next view
 - Go to previous view
 - Move the current file in the following view
 - Move the current file in the previous view
 - Delete the views already present in other groups
 - Delete the views found in other groups
 - Moving a file from one view to the other. Split if it is not already.

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

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$(kde4-config --prefix)
make
sudo make install
```

or

```sh
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$(kde4-config --localprefix)
make
make install
```

Old repository
--------------

https://code.google.com/p/kdevelop-plugin-view-switcher/source/browse/#svn%2Ftrunk%2Ftag-1%253Fstate%253Dclosed
