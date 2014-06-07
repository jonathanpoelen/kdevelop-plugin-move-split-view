kdevelop-plugin-view-switcher
=============================

To switch between the views of KDevelop (file splitter)

INSTALL
-------

### KdevPlatform 14 (Kdevelop 4.4)

sed -i 's/X\-KDevelop\-Version=[0-9][0-9]/X-KDevelop-Version=14/' kdevswitchviewer.desktop

### KdevPlatform 15 (Kdevelop 4.5)

sed -i 's/X\-KDevelop\-Version=[0-9][0-9]/X-KDevelop-Version=15/' kdevswitchviewer.desktop

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
cd cmake .. -DCMAKE_INSTALL_PREFIX=$(kde4-config --localprefix)
make
make install
```

Old repository
--------------

https://code.google.com/p/kdevelop-plugin-view-switcher/source/browse/#svn%2Ftrunk%2Ftag-1%253Fstate%253Dclosed
